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
struct TYPE_2__ {int /*<<< orphan*/  sm_devid; int /*<<< orphan*/  sm_cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cdev_del (int /*<<< orphan*/ *) ; 
 TYPE_1__* sm_state ; 
 int /*<<< orphan*/  unregister_chrdev_region (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int vc_sm_remove_sharedmemory(void)
{
	int ret;

	if (sm_state == NULL) {
		/* Nothing to do. */
		ret = 0;
		goto out;
	}

	/* Remove the sharedmemory character driver. */
	cdev_del(&sm_state->sm_cdev);

	/* Unregister region. */
	unregister_chrdev_region(sm_state->sm_devid, 1);

	ret = 0;
	goto out;

out:
	return ret;
}