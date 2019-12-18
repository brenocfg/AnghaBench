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
typedef  int u8 ;
typedef  int u16 ;
struct ssb_pcicore {int dummy; } ;

/* Variables and functions */
 int ssb_pcicore_polarity_workaround (struct ssb_pcicore*) ; 
 int ssb_pcie_mdio_read (struct ssb_pcicore*,int const,int) ; 
 int /*<<< orphan*/  ssb_pcie_mdio_write (struct ssb_pcicore*,int const,int,int) ; 

__attribute__((used)) static void ssb_pcicore_serdes_workaround(struct ssb_pcicore *pc)
{
	const u8 serdes_pll_device = 0x1D;
	const u8 serdes_rx_device = 0x1F;
	u16 tmp;

	ssb_pcie_mdio_write(pc, serdes_rx_device, 1 /* Control */,
			    ssb_pcicore_polarity_workaround(pc));
	tmp = ssb_pcie_mdio_read(pc, serdes_pll_device, 1 /* Control */);
	if (tmp & 0x4000)
		ssb_pcie_mdio_write(pc, serdes_pll_device, 1, tmp & ~0x4000);
}