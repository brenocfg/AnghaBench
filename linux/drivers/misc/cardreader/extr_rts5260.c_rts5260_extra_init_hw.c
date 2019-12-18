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
struct rtsx_cr_option {scalar_t__ force_clkreq_0; } ;
struct rtsx_pcr {struct rtsx_cr_option option; } ;

/* Variables and functions */
 int FORCE_CLKREQ_DELINK_MASK ; 
 int FORCE_CLKREQ_HIGH ; 
 int FORCE_CLKREQ_LOW ; 
 int LDO_VCC_CFG0 ; 
 int PCLK_CTL ; 
 int PCLK_MODE_SEL ; 
 int PETXCFG ; 
 int RTS5260_AUTOLOAD_CFG4 ; 
 int RTS5260_DVCC_33 ; 
 int RTS5260_DVCC_TUNE_MASK ; 
 int RTS5260_MIMO_DISABLE ; 
 int SSC_DIV_N_0 ; 
 int /*<<< orphan*/  rts5260_init_from_cfg (struct rtsx_pcr*) ; 
 int /*<<< orphan*/  rts5260_init_hw (struct rtsx_pcr*) ; 
 int /*<<< orphan*/  rtsx_pci_write_register (struct rtsx_pcr*,int,int,int) ; 

__attribute__((used)) static int rts5260_extra_init_hw(struct rtsx_pcr *pcr)
{
	struct rtsx_cr_option *option = &pcr->option;

	/* Set mcu_cnt to 7 to ensure data can be sampled properly */
	rtsx_pci_write_register(pcr, 0xFC03, 0x7F, 0x07);
	rtsx_pci_write_register(pcr, SSC_DIV_N_0, 0xFF, 0x5D);

	rts5260_init_from_cfg(pcr);

	/* force no MDIO*/
	rtsx_pci_write_register(pcr, RTS5260_AUTOLOAD_CFG4,
				0xFF, RTS5260_MIMO_DISABLE);
	/*Modify SDVCC Tune Default Parameters!*/
	rtsx_pci_write_register(pcr, LDO_VCC_CFG0,
				RTS5260_DVCC_TUNE_MASK, RTS5260_DVCC_33);

	rtsx_pci_write_register(pcr, PCLK_CTL, PCLK_MODE_SEL, PCLK_MODE_SEL);

	rts5260_init_hw(pcr);

	/*
	 * If u_force_clkreq_0 is enabled, CLKREQ# PIN will be forced
	 * to drive low, and we forcibly request clock.
	 */
	if (option->force_clkreq_0)
		rtsx_pci_write_register(pcr, PETXCFG,
				 FORCE_CLKREQ_DELINK_MASK, FORCE_CLKREQ_LOW);
	else
		rtsx_pci_write_register(pcr, PETXCFG,
				 FORCE_CLKREQ_DELINK_MASK, FORCE_CLKREQ_HIGH);

	return 0;
}