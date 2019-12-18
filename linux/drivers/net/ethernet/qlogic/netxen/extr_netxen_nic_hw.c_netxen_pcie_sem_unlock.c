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
struct netxen_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NETXEN_PCIE_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NXRD32 (struct netxen_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCIE_SEM_UNLOCK (int) ; 

void
netxen_pcie_sem_unlock(struct netxen_adapter *adapter, int sem)
{
	NXRD32(adapter, NETXEN_PCIE_REG(PCIE_SEM_UNLOCK(sem)));
}