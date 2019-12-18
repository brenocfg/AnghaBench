#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct device {int dummy; } ;
struct altera_pcie {TYPE_2__* pcie_data; int /*<<< orphan*/  root_bus_nr; TYPE_3__* pdev; } ;
struct TYPE_6__ {struct device dev; } ;
struct TYPE_5__ {TYPE_1__* ops; } ;
struct TYPE_4__ {scalar_t__ (* get_link_status ) (struct altera_pcie*) ;} ;

/* Variables and functions */
 scalar_t__ LINK_RETRAIN_TIMEOUT ; 
 scalar_t__ LINK_UP_TIMEOUT ; 
 int /*<<< orphan*/  PCI_EXP_LNKSTA ; 
 int PCI_EXP_LNKSTA_LT ; 
 int /*<<< orphan*/  RP_DEVFN ; 
 int /*<<< orphan*/  altera_read_cap_word (struct altera_pcie*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 unsigned long jiffies ; 
 scalar_t__ stub1 (struct altera_pcie*) ; 
 scalar_t__ time_after (unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void altera_wait_link_retrain(struct altera_pcie *pcie)
{
	struct device *dev = &pcie->pdev->dev;
	u16 reg16;
	unsigned long start_jiffies;

	/* Wait for link training end. */
	start_jiffies = jiffies;
	for (;;) {
		altera_read_cap_word(pcie, pcie->root_bus_nr, RP_DEVFN,
				     PCI_EXP_LNKSTA, &reg16);
		if (!(reg16 & PCI_EXP_LNKSTA_LT))
			break;

		if (time_after(jiffies, start_jiffies + LINK_RETRAIN_TIMEOUT)) {
			dev_err(dev, "link retrain timeout\n");
			break;
		}
		udelay(100);
	}

	/* Wait for link is up */
	start_jiffies = jiffies;
	for (;;) {
		if (pcie->pcie_data->ops->get_link_status(pcie))
			break;

		if (time_after(jiffies, start_jiffies + LINK_UP_TIMEOUT)) {
			dev_err(dev, "link up timeout\n");
			break;
		}
		udelay(100);
	}
}