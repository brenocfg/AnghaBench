#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct resource {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_3__ dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  end; scalar_t__ start; } ;
struct TYPE_6__ {int /*<<< orphan*/  end; scalar_t__ start; } ;

/* Variables and functions */
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LC_CKDRVPD ; 
#define  MT762X_SOC_MT7620A 130 
#define  MT762X_SOC_MT7628AN 129 
#define  MT762X_SOC_MT7688 128 
 int PCIE_LINK_UP_ST ; 
 int /*<<< orphan*/  PCIINT2 ; 
 int /*<<< orphan*/  PCIRST ; 
 int /*<<< orphan*/  PDRV_SW_SET ; 
 int /*<<< orphan*/  PPLL_DRV ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RALINK_CLKCFG1 ; 
 int /*<<< orphan*/  RALINK_PCI0_BAR0SETUP_ADDR ; 
 int /*<<< orphan*/  RALINK_PCI0_CLASS ; 
 int /*<<< orphan*/  RALINK_PCI0_IMBASEBAR0_ADDR ; 
 int /*<<< orphan*/  RALINK_PCI0_STATUS ; 
 int /*<<< orphan*/  RALINK_PCIE0_CLK_EN ; 
 int /*<<< orphan*/  RALINK_PCI_IOBASE ; 
 int RALINK_PCI_IO_MAP_BASE ; 
 int /*<<< orphan*/  RALINK_PCI_MEMBASE ; 
 int RALINK_PCI_MEMORY_BASE ; 
 int /*<<< orphan*/  RALINK_PCI_PCICFG_ADDR ; 
 int /*<<< orphan*/  RALINK_PCI_PCIENA ; 
 int /*<<< orphan*/  bridge_base ; 
 int /*<<< orphan*/  bridge_w32 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_3__*,struct resource*) ; 
 int /*<<< orphan*/  devm_reset_control_get_exclusive (TYPE_3__*,char*) ; 
 TYPE_2__ iomem_resource ; 
 TYPE_1__ ioport_resource ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  mt7620_controller ; 
 int /*<<< orphan*/  mt7620_pci_hw_init (struct platform_device*) ; 
 int /*<<< orphan*/  mt7628_pci_hw_init (struct platform_device*) ; 
 int /*<<< orphan*/  pci_config_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int*) ; 
 int /*<<< orphan*/  pci_config_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  pci_load_of_ranges (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcie_base ; 
 int /*<<< orphan*/  pcie_m32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pcie_r32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcie_w32 (int,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int) ; 
 int ralink_soc ; 
 int /*<<< orphan*/  register_pci_controller (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rstpcie0 ; 
 int /*<<< orphan*/  rt_sysc_m32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mt7620_pci_probe(struct platform_device *pdev)
{
	struct resource *bridge_res = platform_get_resource(pdev,
							    IORESOURCE_MEM, 0);
	struct resource *pcie_res = platform_get_resource(pdev,
							  IORESOURCE_MEM, 1);
	u32 val = 0;

	rstpcie0 = devm_reset_control_get_exclusive(&pdev->dev, "pcie0");
	if (IS_ERR(rstpcie0))
		return PTR_ERR(rstpcie0);

	bridge_base = devm_ioremap_resource(&pdev->dev, bridge_res);
	if (IS_ERR(bridge_base))
		return PTR_ERR(bridge_base);

	pcie_base = devm_ioremap_resource(&pdev->dev, pcie_res);
	if (IS_ERR(pcie_base))
		return PTR_ERR(pcie_base);

	iomem_resource.start = 0;
	iomem_resource.end = ~0;
	ioport_resource.start = 0;
	ioport_resource.end = ~0;

	/* bring up the pci core */
	switch (ralink_soc) {
	case MT762X_SOC_MT7620A:
		if (mt7620_pci_hw_init(pdev))
			return -1;
		break;

	case MT762X_SOC_MT7628AN:
	case MT762X_SOC_MT7688:
		if (mt7628_pci_hw_init(pdev))
			return -1;
		break;

	default:
		dev_err(&pdev->dev, "pcie is not supported on this hardware\n");
		return -1;
	}
	mdelay(50);

	/* enable write access */
	pcie_m32(PCIRST, 0, RALINK_PCI_PCICFG_ADDR);
	mdelay(100);

	/* check if there is a card present */
	if ((pcie_r32(RALINK_PCI0_STATUS) & PCIE_LINK_UP_ST) == 0) {
		reset_control_assert(rstpcie0);
		rt_sysc_m32(RALINK_PCIE0_CLK_EN, 0, RALINK_CLKCFG1);
		if (ralink_soc == MT762X_SOC_MT7620A)
			rt_sysc_m32(LC_CKDRVPD, PDRV_SW_SET, PPLL_DRV);
		dev_err(&pdev->dev, "PCIE0 no card, disable it(RST&CLK)\n");
		return -1;
	}

	/* setup ranges */
	bridge_w32(0xffffffff, RALINK_PCI_MEMBASE);
	bridge_w32(RALINK_PCI_IO_MAP_BASE, RALINK_PCI_IOBASE);

	pcie_w32(0x7FFF0001, RALINK_PCI0_BAR0SETUP_ADDR);
	pcie_w32(RALINK_PCI_MEMORY_BASE, RALINK_PCI0_IMBASEBAR0_ADDR);
	pcie_w32(0x06040001, RALINK_PCI0_CLASS);

	/* enable interrupts */
	pcie_m32(0, PCIINT2, RALINK_PCI_PCIENA);

	/* voodoo from the SDK driver */
	pci_config_read(NULL, 0, 4, 4, &val);
	pci_config_write(NULL, 0, 4, 4, val | 0x7);

	pci_load_of_ranges(&mt7620_controller, pdev->dev.of_node);
	register_pci_controller(&mt7620_controller);

	return 0;
}