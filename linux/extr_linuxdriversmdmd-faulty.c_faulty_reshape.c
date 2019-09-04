#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mddev {int new_layout; int layout; struct faulty_conf* private; } ;
struct faulty_conf {int* period; int /*<<< orphan*/ * counters; scalar_t__ nfaults; } ;

/* Variables and functions */
 int ClearErrors ; 
 int ClearFaults ; 
 int EINVAL ; 
 int ModeMask ; 
 int ModeShift ; 
 int Modes ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int faulty_reshape(struct mddev *mddev)
{
	int mode = mddev->new_layout & ModeMask;
	int count = mddev->new_layout >> ModeShift;
	struct faulty_conf *conf = mddev->private;

	if (mddev->new_layout < 0)
		return 0;

	/* new layout */
	if (mode == ClearFaults)
		conf->nfaults = 0;
	else if (mode == ClearErrors) {
		int i;
		for (i=0 ; i < Modes ; i++) {
			conf->period[i] = 0;
			atomic_set(&conf->counters[i], 0);
		}
	} else if (mode < Modes) {
		conf->period[mode] = count;
		if (!count) count++;
		atomic_set(&conf->counters[mode], count);
	} else
		return -EINVAL;
	mddev->new_layout = -1;
	mddev->layout = -1; /* makes sure further changes come through */
	return 0;
}