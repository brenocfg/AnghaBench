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
struct pvr2_ioread {int /*<<< orphan*/  mutex; int /*<<< orphan*/  enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pvr2_ioread_start (struct pvr2_ioread*) ; 
 int /*<<< orphan*/  pvr2_ioread_stop (struct pvr2_ioread*) ; 

int pvr2_ioread_set_enabled(struct pvr2_ioread *cp,int fl)
{
	int ret = 0;
	if ((!fl) == (!(cp->enabled))) return ret;

	mutex_lock(&cp->mutex);
	do {
		if (fl) {
			ret = pvr2_ioread_start(cp);
		} else {
			pvr2_ioread_stop(cp);
		}
	} while (0);
	mutex_unlock(&cp->mutex);
	return ret;
}