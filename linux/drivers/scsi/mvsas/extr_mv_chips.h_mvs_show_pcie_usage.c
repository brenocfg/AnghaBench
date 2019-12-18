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
typedef  int u16 ;
struct mvs_info {int flags; scalar_t__ id; int /*<<< orphan*/  dev; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INFO ; 
 int MVF_FLAG_SOC ; 
 int /*<<< orphan*/  PCR_LINK_STAT ; 
 int PLS_LINK_SPD ; 
 int PLS_LINK_SPD_OFFS ; 
 int PLS_NEG_LINK_WD ; 
 int PLS_NEG_LINK_WD_OFFS ; 
 int /*<<< orphan*/  dev_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,char const*) ; 
 int /*<<< orphan*/  pci_read_config_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static inline void mvs_show_pcie_usage(struct mvs_info *mvi)
{
	u16 link_stat, link_spd;
	const char *spd[] = {
		"UnKnown",
		"2.5",
		"5.0",
	};
	if (mvi->flags & MVF_FLAG_SOC || mvi->id > 0)
		return;

	pci_read_config_word(mvi->pdev, PCR_LINK_STAT, &link_stat);
	link_spd = (link_stat & PLS_LINK_SPD) >> PLS_LINK_SPD_OFFS;
	if (link_spd >= 3)
		link_spd = 0;
	dev_printk(KERN_INFO, mvi->dev,
		"mvsas: PCI-E x%u, Bandwidth Usage: %s Gbps\n",
	       (link_stat & PLS_NEG_LINK_WD) >> PLS_NEG_LINK_WD_OFFS,
	       spd[link_spd]);
}