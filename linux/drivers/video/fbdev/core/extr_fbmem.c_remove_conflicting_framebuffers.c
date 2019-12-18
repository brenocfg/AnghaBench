#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct apertures_struct {TYPE_1__* ranges; } ;
struct TYPE_2__ {int /*<<< orphan*/  size; scalar_t__ base; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct apertures_struct* alloc_apertures (int) ; 
 int /*<<< orphan*/  do_remove_conflicting_framebuffers (struct apertures_struct*,char const*,int) ; 
 int /*<<< orphan*/  kfree (struct apertures_struct*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  registration_lock ; 

int remove_conflicting_framebuffers(struct apertures_struct *a,
				    const char *name, bool primary)
{
	bool do_free = false;

	if (!a) {
		a = alloc_apertures(1);
		if (!a)
			return -ENOMEM;

		a->ranges[0].base = 0;
		a->ranges[0].size = ~0;
		do_free = true;
	}

	mutex_lock(&registration_lock);
	do_remove_conflicting_framebuffers(a, name, primary);
	mutex_unlock(&registration_lock);

	if (do_free)
		kfree(a);

	return 0;
}