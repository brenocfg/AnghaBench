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
struct ccw_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZFCP_STATUS_ADAPTER_SUSPENDED ; 
 int /*<<< orphan*/  zfcp_ccw_offline_sync (struct ccw_device*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int zfcp_ccw_suspend(struct ccw_device *cdev)
{
	zfcp_ccw_offline_sync(cdev, ZFCP_STATUS_ADAPTER_SUSPENDED, "ccsusp1");
	return 0;
}