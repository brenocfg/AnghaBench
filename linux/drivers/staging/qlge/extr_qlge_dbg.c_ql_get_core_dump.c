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
struct ql_adapter {int /*<<< orphan*/  ndev; } ;

/* Variables and functions */
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  ifup ; 
 int /*<<< orphan*/  netif_err (struct ql_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netif_running (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_own_firmware (struct ql_adapter*) ; 
 int /*<<< orphan*/  ql_queue_fw_error (struct ql_adapter*) ; 

__attribute__((used)) static void ql_get_core_dump(struct ql_adapter *qdev)
{
	if (!ql_own_firmware(qdev)) {
		netif_err(qdev, drv, qdev->ndev, "Don't own firmware!\n");
		return;
	}

	if (!netif_running(qdev->ndev)) {
		netif_err(qdev, ifup, qdev->ndev,
			  "Force Coredump can only be done from interface that is up\n");
		return;
	}
	ql_queue_fw_error(qdev);
}