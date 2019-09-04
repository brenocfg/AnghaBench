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
typedef  int u32 ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  RALINK_CLKCFG1 ; 
 int /*<<< orphan*/  RALINK_GPIOMODE ; 
 int /*<<< orphan*/  RALINK_PCIE0_CLK_EN ; 
 int /*<<< orphan*/  RALINK_PCIEPHY_P0_CTL_OFFSET ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,unsigned int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  pci_config_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int*) ; 
 int /*<<< orphan*/  pci_config_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  pcie_m32 (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_deassert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rstpcie0 ; 
 int /*<<< orphan*/  rt_sysc_m32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mt7628_pci_hw_init(struct platform_device *pdev)
{
	u32 val = 0;

	/* bring the core out of reset */
	rt_sysc_m32(BIT(16), 0, RALINK_GPIOMODE);
	reset_control_deassert(rstpcie0);

	/* enable the pci clk */
	rt_sysc_m32(0, RALINK_PCIE0_CLK_EN, RALINK_CLKCFG1);
	mdelay(100);

	/* voodoo from the SDK driver */
	pcie_m32(~0xff, 0x5, RALINK_PCIEPHY_P0_CTL_OFFSET);

	pci_config_read(NULL, 0, 0x70c, 4, &val);
	val &= ~(0xff) << 8;
	val |= 0x50 << 8;
	pci_config_write(NULL, 0, 0x70c, 4, val);

	pci_config_read(NULL, 0, 0x70c, 4, &val);
	dev_err(&pdev->dev, "Port 0 N_FTS = %x\n", (unsigned int) val);

	return 0;
}