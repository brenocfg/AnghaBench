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
struct TYPE_2__ {int initialized; int /*<<< orphan*/  bdev; } ;
struct bochs_device {TYPE_1__ ttm; } ;

/* Variables and functions */
 int /*<<< orphan*/  bochs_ttm_global_release (struct bochs_device*) ; 
 int /*<<< orphan*/  ttm_bo_device_release (int /*<<< orphan*/ *) ; 

void bochs_mm_fini(struct bochs_device *bochs)
{
	if (!bochs->ttm.initialized)
		return;

	ttm_bo_device_release(&bochs->ttm.bdev);
	bochs_ttm_global_release(bochs);
	bochs->ttm.initialized = false;
}