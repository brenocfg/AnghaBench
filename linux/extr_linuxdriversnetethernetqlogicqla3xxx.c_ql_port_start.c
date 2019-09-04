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
 int /*<<< orphan*/  QL_PHY_GIO_SEM_MASK ; 
 int QL_RESOURCE_BITS_BASE_CODE ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ql_is_fiber (struct ql3_adapter*) ; 
 int /*<<< orphan*/  ql_petbi_init (struct ql3_adapter*) ; 
 int /*<<< orphan*/  ql_phy_init_ex (struct ql3_adapter*) ; 
 scalar_t__ ql_sem_spinlock (struct ql3_adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ql_sem_unlock (struct ql3_adapter*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ql_port_start(struct ql3_adapter *qdev)
{
	if (ql_sem_spinlock(qdev, QL_PHY_GIO_SEM_MASK,
		(QL_RESOURCE_BITS_BASE_CODE | (qdev->mac_index) *
			 2) << 7)) {
		netdev_err(qdev->ndev, "Could not get hw lock for GIO\n");
		return -1;
	}

	if (ql_is_fiber(qdev)) {
		ql_petbi_init(qdev);
	} else {
		/* Copper port */
		ql_phy_init_ex(qdev);
	}

	ql_sem_unlock(qdev, QL_PHY_GIO_SEM_MASK);
	return 0;
}