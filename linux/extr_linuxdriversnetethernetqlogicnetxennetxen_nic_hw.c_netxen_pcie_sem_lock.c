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
typedef  scalar_t__ u32 ;
struct netxen_adapter {int /*<<< orphan*/  portnum; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  NETXEN_PCIE_REG (int /*<<< orphan*/ ) ; 
 int NETXEN_PCIE_SEM_TIMEOUT ; 
 int NXRD32 (struct netxen_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NXWR32 (struct netxen_adapter*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCIE_SEM_LOCK (int) ; 
 int /*<<< orphan*/  msleep (int) ; 

int
netxen_pcie_sem_lock(struct netxen_adapter *adapter, int sem, u32 id_reg)
{
	int done = 0, timeout = 0;

	while (!done) {
		done = NXRD32(adapter, NETXEN_PCIE_REG(PCIE_SEM_LOCK(sem)));
		if (done == 1)
			break;
		if (++timeout >= NETXEN_PCIE_SEM_TIMEOUT)
			return -EIO;
		msleep(1);
	}

	if (id_reg)
		NXWR32(adapter, id_reg, adapter->portnum);

	return 0;
}