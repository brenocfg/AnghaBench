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
struct ttm_operation_ctx {int interruptible; int no_wait_gpu; } ;
struct ttm_bo_device {int /*<<< orphan*/  glob; } ;

/* Variables and functions */
 scalar_t__ ttm_bo_swapout (int /*<<< orphan*/ ,struct ttm_operation_ctx*) ; 

void ttm_bo_swapout_all(struct ttm_bo_device *bdev)
{
	struct ttm_operation_ctx ctx = {
		.interruptible = false,
		.no_wait_gpu = false
	};

	while (ttm_bo_swapout(bdev->glob, &ctx) == 0)
		;
}