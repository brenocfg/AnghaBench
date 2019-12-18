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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct rockchip_pcie {int dummy; } ;
struct rockchip_pcie_ep {struct rockchip_pcie rockchip; } ;
struct pci_epf_bar {int barno; } ;
struct pci_epc {int dummy; } ;
typedef  enum pci_barno { ____Placeholder_pci_barno } pci_barno ;

/* Variables and functions */
 int BAR_4 ; 
 int ROCKCHIP_PCIE_AT_IB_EP_FUNC_BAR_ADDR0 (int /*<<< orphan*/ ,int) ; 
 int ROCKCHIP_PCIE_AT_IB_EP_FUNC_BAR_ADDR1 (int /*<<< orphan*/ ,int) ; 
 int ROCKCHIP_PCIE_CORE_BAR_CFG_CTRL_DISABLED ; 
 int ROCKCHIP_PCIE_CORE_EP_FUNC_BAR_CFG0 (int /*<<< orphan*/ ) ; 
 int ROCKCHIP_PCIE_CORE_EP_FUNC_BAR_CFG1 (int /*<<< orphan*/ ) ; 
 int ROCKCHIP_PCIE_CORE_EP_FUNC_BAR_CFG_BAR_APERTURE_MASK (int) ; 
 int ROCKCHIP_PCIE_CORE_EP_FUNC_BAR_CFG_BAR_CTRL (int,int) ; 
 int ROCKCHIP_PCIE_CORE_EP_FUNC_BAR_CFG_BAR_CTRL_MASK (int) ; 
 struct rockchip_pcie_ep* epc_get_drvdata (struct pci_epc*) ; 
 int rockchip_pcie_read (struct rockchip_pcie*,int) ; 
 int /*<<< orphan*/  rockchip_pcie_write (struct rockchip_pcie*,int,int) ; 

__attribute__((used)) static void rockchip_pcie_ep_clear_bar(struct pci_epc *epc, u8 fn,
				       struct pci_epf_bar *epf_bar)
{
	struct rockchip_pcie_ep *ep = epc_get_drvdata(epc);
	struct rockchip_pcie *rockchip = &ep->rockchip;
	u32 reg, cfg, b, ctrl;
	enum pci_barno bar = epf_bar->barno;

	if (bar < BAR_4) {
		reg = ROCKCHIP_PCIE_CORE_EP_FUNC_BAR_CFG0(fn);
		b = bar;
	} else {
		reg = ROCKCHIP_PCIE_CORE_EP_FUNC_BAR_CFG1(fn);
		b = bar - BAR_4;
	}

	ctrl = ROCKCHIP_PCIE_CORE_BAR_CFG_CTRL_DISABLED;
	cfg = rockchip_pcie_read(rockchip, reg);
	cfg &= ~(ROCKCHIP_PCIE_CORE_EP_FUNC_BAR_CFG_BAR_APERTURE_MASK(b) |
		 ROCKCHIP_PCIE_CORE_EP_FUNC_BAR_CFG_BAR_CTRL_MASK(b));
	cfg |= ROCKCHIP_PCIE_CORE_EP_FUNC_BAR_CFG_BAR_CTRL(b, ctrl);

	rockchip_pcie_write(rockchip, cfg, reg);
	rockchip_pcie_write(rockchip, 0x0,
			    ROCKCHIP_PCIE_AT_IB_EP_FUNC_BAR_ADDR0(fn, bar));
	rockchip_pcie_write(rockchip, 0x0,
			    ROCKCHIP_PCIE_AT_IB_EP_FUNC_BAR_ADDR1(fn, bar));
}