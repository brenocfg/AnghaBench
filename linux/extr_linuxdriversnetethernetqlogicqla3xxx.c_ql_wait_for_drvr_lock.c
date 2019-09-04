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
struct ql3_adapter {int mac_index; int /*<<< orphan*/  ndev; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  QL_DRVR_SEM_MASK ; 
 int QL_RESOURCE_BITS_BASE_CODE ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netdev_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ql_sem_lock (struct ql3_adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ssleep (int) ; 

__attribute__((used)) static int ql_wait_for_drvr_lock(struct ql3_adapter *qdev)
{
	int i = 0;

	do {
		if (ql_sem_lock(qdev,
				QL_DRVR_SEM_MASK,
				(QL_RESOURCE_BITS_BASE_CODE | (qdev->mac_index)
				 * 2) << 1)) {
			netdev_printk(KERN_DEBUG, qdev->ndev,
				      "driver lock acquired\n");
			return 1;
		}
		ssleep(1);
	} while (++i < 10);

	netdev_err(qdev->ndev, "Timed out waiting for driver lock...\n");
	return 0;
}