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
struct device {int dummy; } ;
struct ufs_hba {int /*<<< orphan*/  bsg_queue; struct device bsg_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  bsg_remove_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_del (struct device*) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 

void ufs_bsg_remove(struct ufs_hba *hba)
{
	struct device *bsg_dev = &hba->bsg_dev;

	if (!hba->bsg_queue)
		return;

	bsg_remove_queue(hba->bsg_queue);

	device_del(bsg_dev);
	put_device(bsg_dev);
}