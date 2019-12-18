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
struct copy_block_struct {int /*<<< orphan*/  wait; int /*<<< orphan*/  ret; } ;
struct ccw_device {TYPE_1__* private; } ;
struct TYPE_2__ {struct copy_block_struct* cmb_wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  cmf_copy_block (struct ccw_device*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void cmf_retry_copy_block(struct ccw_device *cdev)
{
	struct copy_block_struct *copy_block = cdev->private->cmb_wait;

	if (!copy_block)
		return;

	copy_block->ret = cmf_copy_block(cdev);
	wake_up(&copy_block->wait);
}