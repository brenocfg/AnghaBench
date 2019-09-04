#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct driver_data {TYPE_2__* disk; TYPE_1__* pdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  disk_name; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtip_hw_resume (struct driver_data*) ; 

__attribute__((used)) static int mtip_block_resume(struct driver_data *dd)
{
	dev_info(&dd->pdev->dev, "Resuming %s ...\n",
		dd->disk->disk_name);
	mtip_hw_resume(dd);
	return 0;
}