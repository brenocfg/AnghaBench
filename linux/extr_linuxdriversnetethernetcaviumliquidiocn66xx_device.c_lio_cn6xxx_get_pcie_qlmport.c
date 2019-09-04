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
struct octeon_device {int pcie_port; TYPE_1__* pci_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CN6XXX_SLI_MAC_NUMBER ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int octeon_read_csr (struct octeon_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lio_cn6xxx_get_pcie_qlmport(struct octeon_device *oct)
{
	/* CN63xx Pass2 and newer parts implements the SLI_MAC_NUMBER register
	 * to determine the PCIE port #
	 */
	oct->pcie_port = octeon_read_csr(oct, CN6XXX_SLI_MAC_NUMBER) & 0xff;

	dev_dbg(&oct->pci_dev->dev, "Using PCIE Port %d\n", oct->pcie_port);
}