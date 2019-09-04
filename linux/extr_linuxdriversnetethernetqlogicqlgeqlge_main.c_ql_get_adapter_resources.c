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
 int ENOMEM ; 
 int /*<<< orphan*/  ifup ; 
 int /*<<< orphan*/  netif_err (struct ql_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ql_alloc_mem_resources (struct ql_adapter*) ; 
 int ql_request_irq (struct ql_adapter*) ; 

__attribute__((used)) static int ql_get_adapter_resources(struct ql_adapter *qdev)
{
	int status = 0;

	if (ql_alloc_mem_resources(qdev)) {
		netif_err(qdev, ifup, qdev->ndev, "Unable to  allocate memory.\n");
		return -ENOMEM;
	}
	status = ql_request_irq(qdev);
	return status;
}