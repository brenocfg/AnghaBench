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
typedef  scalar_t__ u16 ;
struct TYPE_2__ {void* timing_2; void* timing_1; void* acc_control; void* config_ext; void* config; } ;
struct brcmnand_host {TYPE_1__ hwcfg; int /*<<< orphan*/  cs; struct brcmnand_controller* ctrl; } ;
struct brcmnand_controller {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMNAND_CS_ACC_CONTROL ; 
 int /*<<< orphan*/  BRCMNAND_CS_CFG ; 
 int /*<<< orphan*/  BRCMNAND_CS_CFG_EXT ; 
 int /*<<< orphan*/  BRCMNAND_CS_TIMING1 ; 
 int /*<<< orphan*/  BRCMNAND_CS_TIMING2 ; 
 scalar_t__ brcmnand_cs_offset (struct brcmnand_controller*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* nand_readreg (struct brcmnand_controller*,scalar_t__) ; 
 int /*<<< orphan*/  nand_writereg (struct brcmnand_controller*,scalar_t__,void*) ; 

__attribute__((used)) static void brcmnand_save_restore_cs_config(struct brcmnand_host *host,
					    int restore)
{
	struct brcmnand_controller *ctrl = host->ctrl;
	u16 cfg_offs = brcmnand_cs_offset(ctrl, host->cs, BRCMNAND_CS_CFG);
	u16 cfg_ext_offs = brcmnand_cs_offset(ctrl, host->cs,
			BRCMNAND_CS_CFG_EXT);
	u16 acc_control_offs = brcmnand_cs_offset(ctrl, host->cs,
			BRCMNAND_CS_ACC_CONTROL);
	u16 t1_offs = brcmnand_cs_offset(ctrl, host->cs, BRCMNAND_CS_TIMING1);
	u16 t2_offs = brcmnand_cs_offset(ctrl, host->cs, BRCMNAND_CS_TIMING2);

	if (restore) {
		nand_writereg(ctrl, cfg_offs, host->hwcfg.config);
		if (cfg_offs != cfg_ext_offs)
			nand_writereg(ctrl, cfg_ext_offs,
				      host->hwcfg.config_ext);
		nand_writereg(ctrl, acc_control_offs, host->hwcfg.acc_control);
		nand_writereg(ctrl, t1_offs, host->hwcfg.timing_1);
		nand_writereg(ctrl, t2_offs, host->hwcfg.timing_2);
	} else {
		host->hwcfg.config = nand_readreg(ctrl, cfg_offs);
		if (cfg_offs != cfg_ext_offs)
			host->hwcfg.config_ext =
				nand_readreg(ctrl, cfg_ext_offs);
		host->hwcfg.acc_control = nand_readreg(ctrl, acc_control_offs);
		host->hwcfg.timing_1 = nand_readreg(ctrl, t1_offs);
		host->hwcfg.timing_2 = nand_readreg(ctrl, t2_offs);
	}
}