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
struct c8sectpfe_hw {void* num_tp; void* num_ram; void* num_ccsc; void* num_tsout; void* num_swts; void* num_mib; void* num_ib; } ;
struct c8sectpfei {int /*<<< orphan*/  dev; scalar_t__ io; struct c8sectpfe_hw hw_stats; } ;

/* Variables and functions */
 scalar_t__ SYS_CFG_NUM_CCSC ; 
 scalar_t__ SYS_CFG_NUM_IB ; 
 scalar_t__ SYS_CFG_NUM_MIB ; 
 scalar_t__ SYS_CFG_NUM_RAM ; 
 scalar_t__ SYS_CFG_NUM_SWTS ; 
 scalar_t__ SYS_CFG_NUM_TP ; 
 scalar_t__ SYS_CFG_NUM_TSOUT ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,...) ; 
 void* readl (scalar_t__) ; 

__attribute__((used)) static void c8sectpfe_getconfig(struct c8sectpfei *fei)
{
	struct c8sectpfe_hw *hw = &fei->hw_stats;

	hw->num_ib = readl(fei->io + SYS_CFG_NUM_IB);
	hw->num_mib = readl(fei->io + SYS_CFG_NUM_MIB);
	hw->num_swts = readl(fei->io + SYS_CFG_NUM_SWTS);
	hw->num_tsout = readl(fei->io + SYS_CFG_NUM_TSOUT);
	hw->num_ccsc = readl(fei->io + SYS_CFG_NUM_CCSC);
	hw->num_ram = readl(fei->io + SYS_CFG_NUM_RAM);
	hw->num_tp = readl(fei->io + SYS_CFG_NUM_TP);

	dev_info(fei->dev, "C8SECTPFE hw supports the following:\n");
	dev_info(fei->dev, "Input Blocks: %d\n", hw->num_ib);
	dev_info(fei->dev, "Merged Input Blocks: %d\n", hw->num_mib);
	dev_info(fei->dev, "Software Transport Stream Inputs: %d\n"
				, hw->num_swts);
	dev_info(fei->dev, "Transport Stream Output: %d\n", hw->num_tsout);
	dev_info(fei->dev, "Cable Card Converter: %d\n", hw->num_ccsc);
	dev_info(fei->dev, "RAMs supported by C8SECTPFE: %d\n", hw->num_ram);
	dev_info(fei->dev, "Tango TPs supported by C8SECTPFE: %d\n"
			, hw->num_tp);
}