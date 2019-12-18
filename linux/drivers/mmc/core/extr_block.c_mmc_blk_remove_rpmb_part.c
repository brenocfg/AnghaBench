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
struct mmc_rpmb_data {int /*<<< orphan*/  dev; int /*<<< orphan*/  chrdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cdev_device_del (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mmc_blk_remove_rpmb_part(struct mmc_rpmb_data *rpmb)

{
	cdev_device_del(&rpmb->chrdev, &rpmb->dev);
	put_device(&rpmb->dev);
}