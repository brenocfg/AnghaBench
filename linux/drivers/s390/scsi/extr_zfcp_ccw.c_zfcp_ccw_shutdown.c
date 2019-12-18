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
struct zfcp_adapter {int dummy; } ;
struct ccw_device {int dummy; } ;

/* Variables and functions */
 struct zfcp_adapter* zfcp_ccw_adapter_by_cdev (struct ccw_device*) ; 
 int /*<<< orphan*/  zfcp_ccw_adapter_put (struct zfcp_adapter*) ; 
 int /*<<< orphan*/  zfcp_erp_adapter_shutdown (struct zfcp_adapter*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zfcp_erp_thread_kill (struct zfcp_adapter*) ; 
 int /*<<< orphan*/  zfcp_erp_wait (struct zfcp_adapter*) ; 

__attribute__((used)) static void zfcp_ccw_shutdown(struct ccw_device *cdev)
{
	struct zfcp_adapter *adapter = zfcp_ccw_adapter_by_cdev(cdev);

	if (!adapter)
		return;

	zfcp_erp_adapter_shutdown(adapter, 0, "ccshut1");
	zfcp_erp_wait(adapter);
	zfcp_erp_thread_kill(adapter);

	zfcp_ccw_adapter_put(adapter);
}