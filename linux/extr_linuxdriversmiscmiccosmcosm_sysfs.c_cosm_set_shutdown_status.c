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
typedef  size_t u8 ;
struct cosm_device {size_t shutdown_status; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/ * cosm_shutdown_status_string ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void cosm_set_shutdown_status(struct cosm_device *cdev, u8 shutdown_status)
{
	dev_dbg(&cdev->dev, "Shutdown Status %s -> %s\n",
		cosm_shutdown_status_string[cdev->shutdown_status],
		cosm_shutdown_status_string[shutdown_status]);
	cdev->shutdown_status = shutdown_status;
}