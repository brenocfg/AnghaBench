#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  revision_id; } ;
struct netxen_adapter {TYPE_1__ ahw; } ;

/* Variables and functions */
 int EIO ; 
 int NETXEN_BDINFO_MAGIC ; 
 int /*<<< orphan*/  NETXEN_CAM_RAM (int) ; 
 int /*<<< orphan*/  NETXEN_PCIE_REG (int) ; 
 int /*<<< orphan*/  NETXEN_ROMUSB_GLB_PEGTUNE_DONE ; 
 int /*<<< orphan*/  NETXEN_ROMUSB_GLB_SW_RESET ; 
 int NXRD32 (struct netxen_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NXWR32 (struct netxen_adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NX_IS_REVISION_P2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int
netxen_check_hw_init(struct netxen_adapter *adapter, int first_boot)
{
	u32 val, timeout;

	if (first_boot == 0x55555555) {
		/* This is the first boot after power up */
		NXWR32(adapter, NETXEN_CAM_RAM(0x1fc), NETXEN_BDINFO_MAGIC);

		if (!NX_IS_REVISION_P2(adapter->ahw.revision_id))
			return 0;

		/* PCI bus master workaround */
		first_boot = NXRD32(adapter, NETXEN_PCIE_REG(0x4));
		if (!(first_boot & 0x4)) {
			first_boot |= 0x4;
			NXWR32(adapter, NETXEN_PCIE_REG(0x4), first_boot);
			NXRD32(adapter, NETXEN_PCIE_REG(0x4));
		}

		/* This is the first boot after power up */
		first_boot = NXRD32(adapter, NETXEN_ROMUSB_GLB_SW_RESET);
		if (first_boot != 0x80000f) {
			/* clear the register for future unloads/loads */
			NXWR32(adapter, NETXEN_CAM_RAM(0x1fc), 0);
			return -EIO;
		}

		/* Start P2 boot loader */
		val = NXRD32(adapter, NETXEN_ROMUSB_GLB_PEGTUNE_DONE);
		NXWR32(adapter, NETXEN_ROMUSB_GLB_PEGTUNE_DONE, val | 0x1);
		timeout = 0;
		do {
			msleep(1);
			val = NXRD32(adapter, NETXEN_CAM_RAM(0x1fc));

			if (++timeout > 5000)
				return -EIO;

		} while (val == NETXEN_BDINFO_MAGIC);
	}
	return 0;
}