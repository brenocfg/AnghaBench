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
struct TYPE_2__ {char* dev_id; char* con_id; struct clk* clk; } ;
struct clk {TYPE_1__ cl; int /*<<< orphan*/  disable; int /*<<< orphan*/  enable; int /*<<< orphan*/  bits; scalar_t__ module; int /*<<< orphan*/  rates; int /*<<< orphan*/  rate; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_33M ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PMU_PCI ; 
 int /*<<< orphan*/  clkdev_add (TYPE_1__*) ; 
 struct clk* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_enable ; 
 int /*<<< orphan*/  pci_ext_disable ; 
 int /*<<< orphan*/  pci_ext_enable ; 
 int /*<<< orphan*/  pmu_disable ; 
 int /*<<< orphan*/  valid_pci_rates ; 

__attribute__((used)) static void clkdev_add_pci(void)
{
	struct clk *clk = kzalloc(sizeof(struct clk), GFP_KERNEL);
	struct clk *clk_ext = kzalloc(sizeof(struct clk), GFP_KERNEL);

	/* main pci clock */
	clk->cl.dev_id = "17000000.pci";
	clk->cl.con_id = NULL;
	clk->cl.clk = clk;
	clk->rate = CLOCK_33M;
	clk->rates = valid_pci_rates;
	clk->enable = pci_enable;
	clk->disable = pmu_disable;
	clk->module = 0;
	clk->bits = PMU_PCI;
	clkdev_add(&clk->cl);

	/* use internal/external bus clock */
	clk_ext->cl.dev_id = "17000000.pci";
	clk_ext->cl.con_id = "external";
	clk_ext->cl.clk = clk_ext;
	clk_ext->enable = pci_ext_enable;
	clk_ext->disable = pci_ext_disable;
	clkdev_add(&clk_ext->cl);
}