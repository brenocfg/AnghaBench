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
struct ssb_pcicore {struct ssb_device* dev; } ;
struct TYPE_2__ {scalar_t__ coreid; } ;
struct ssb_device {TYPE_1__ id; struct ssb_bus* bus; } ;
struct ssb_bus {scalar_t__ bustype; } ;

/* Variables and functions */
 scalar_t__ SSB_BUSTYPE_PCI ; 
 scalar_t__ SSB_DEV_PCIE ; 
 int /*<<< orphan*/  SSB_INTVEC ; 
 int /*<<< orphan*/  ssb_pcicore_fix_sprom_core_index (struct ssb_pcicore*) ; 
 int /*<<< orphan*/  ssb_pcicore_serdes_workaround (struct ssb_pcicore*) ; 
 int /*<<< orphan*/  ssb_write32 (struct ssb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ssb_pcicore_init_clientmode(struct ssb_pcicore *pc)
{
	struct ssb_device *pdev = pc->dev;
	struct ssb_bus *bus = pdev->bus;

	if (bus->bustype == SSB_BUSTYPE_PCI)
		ssb_pcicore_fix_sprom_core_index(pc);

	/* Disable PCI interrupts. */
	ssb_write32(pdev, SSB_INTVEC, 0);

	/* Additional PCIe always once-executed workarounds */
	if (pc->dev->id.coreid == SSB_DEV_PCIE) {
		ssb_pcicore_serdes_workaround(pc);
		/* TODO: ASPM */
		/* TODO: Clock Request Update */
	}
}