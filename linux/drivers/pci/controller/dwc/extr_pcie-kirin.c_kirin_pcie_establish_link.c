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
struct pcie_port {int dummy; } ;
struct kirin_pcie {TYPE_1__* pci; } ;
struct dw_pcie {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device* dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  LINK_WAIT_MAX ; 
 int /*<<< orphan*/  LINK_WAIT_MIN ; 
 int /*<<< orphan*/  PCIE_APP_LTSSM_ENABLE ; 
 int /*<<< orphan*/  PCIE_LTSSM_ENABLE_BIT ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dw_pcie_setup_rc (struct pcie_port*) ; 
 int /*<<< orphan*/  kirin_apb_ctrl_writel (struct kirin_pcie*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ kirin_pcie_link_up (struct dw_pcie*) ; 
 struct dw_pcie* to_dw_pcie_from_pp (struct pcie_port*) ; 
 struct kirin_pcie* to_kirin_pcie (struct dw_pcie*) ; 
 int /*<<< orphan*/  usleep_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kirin_pcie_establish_link(struct pcie_port *pp)
{
	struct dw_pcie *pci = to_dw_pcie_from_pp(pp);
	struct kirin_pcie *kirin_pcie = to_kirin_pcie(pci);
	struct device *dev = kirin_pcie->pci->dev;
	int count = 0;

	if (kirin_pcie_link_up(pci))
		return 0;

	dw_pcie_setup_rc(pp);

	/* assert LTSSM enable */
	kirin_apb_ctrl_writel(kirin_pcie, PCIE_LTSSM_ENABLE_BIT,
			      PCIE_APP_LTSSM_ENABLE);

	/* check if the link is up or not */
	while (!kirin_pcie_link_up(pci)) {
		usleep_range(LINK_WAIT_MIN, LINK_WAIT_MAX);
		count++;
		if (count == 1000) {
			dev_err(dev, "Link Fail\n");
			return -EINVAL;
		}
	}

	return 0;
}