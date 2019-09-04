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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  CR_REG_TIMER ; 
 int /*<<< orphan*/  CR_TIME_SCALE ; 
 int /*<<< orphan*/  M_CSYSREQ ; 
 int /*<<< orphan*/  P0_IPDIPDMSYNTH ; 
 int /*<<< orphan*/  P0_IPDRXL ; 
 int /*<<< orphan*/  P0_IPDTXL ; 
 int /*<<< orphan*/  P0_IRST_HARD_SYNTH ; 
 int /*<<< orphan*/  P0_IRST_HARD_TXRX ; 
 int /*<<< orphan*/  P0_IRST_POR ; 
 int P0_PHY_READY ; 
 int /*<<< orphan*/  P1_IPDIPDMSYNTH ; 
 int /*<<< orphan*/  P1_IPDRXL ; 
 int /*<<< orphan*/  P1_IPDTXL ; 
 int /*<<< orphan*/  P1_IRST_HARD_SYNTH ; 
 int /*<<< orphan*/  P1_IRST_HARD_TXRX ; 
 int /*<<< orphan*/  P1_IRST_POR ; 
 int P1_PHY_READY ; 
 int /*<<< orphan*/  SATA_CTL ; 
 int /*<<< orphan*/  SATA_RST_N ; 
 int /*<<< orphan*/  SATA_STATUS ; 
 int /*<<< orphan*/  S_CSYSREQ ; 
 int /*<<< orphan*/  config_sata_phy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_get_sata_regbase (int) ; 
 int nlm_read_sata_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  sata_clear_glue_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sata_phy_debug ; 
 int /*<<< orphan*/  sata_set_glue_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  verify_sata_phy_config (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nlm_sata_firmware_init(int node)
{
	u32 reg_val;
	u64 regbase;
	int n;

	pr_info("Initializing XLP9XX On-chip AHCI...\n");
	regbase = nlm_get_sata_regbase(node);

	/* Reset port0 */
	sata_clear_glue_reg(regbase, SATA_CTL, P0_IRST_POR);
	sata_clear_glue_reg(regbase, SATA_CTL, P0_IRST_HARD_TXRX);
	sata_clear_glue_reg(regbase, SATA_CTL, P0_IRST_HARD_SYNTH);
	sata_clear_glue_reg(regbase, SATA_CTL, P0_IPDTXL);
	sata_clear_glue_reg(regbase, SATA_CTL, P0_IPDRXL);
	sata_clear_glue_reg(regbase, SATA_CTL, P0_IPDIPDMSYNTH);

	/* port1 */
	sata_clear_glue_reg(regbase, SATA_CTL, P1_IRST_POR);
	sata_clear_glue_reg(regbase, SATA_CTL, P1_IRST_HARD_TXRX);
	sata_clear_glue_reg(regbase, SATA_CTL, P1_IRST_HARD_SYNTH);
	sata_clear_glue_reg(regbase, SATA_CTL, P1_IPDTXL);
	sata_clear_glue_reg(regbase, SATA_CTL, P1_IPDRXL);
	sata_clear_glue_reg(regbase, SATA_CTL, P1_IPDIPDMSYNTH);
	udelay(300);

	/* Set PHY */
	sata_set_glue_reg(regbase, SATA_CTL, P0_IPDTXL);
	sata_set_glue_reg(regbase, SATA_CTL, P0_IPDRXL);
	sata_set_glue_reg(regbase, SATA_CTL, P0_IPDIPDMSYNTH);
	sata_set_glue_reg(regbase, SATA_CTL, P1_IPDTXL);
	sata_set_glue_reg(regbase, SATA_CTL, P1_IPDRXL);
	sata_set_glue_reg(regbase, SATA_CTL, P1_IPDIPDMSYNTH);

	udelay(1000);
	sata_set_glue_reg(regbase, SATA_CTL, P0_IRST_POR);
	udelay(1000);
	sata_set_glue_reg(regbase, SATA_CTL, P1_IRST_POR);
	udelay(1000);

	/* setup PHY */
	config_sata_phy(regbase);
	if (sata_phy_debug)
		verify_sata_phy_config(regbase);

	udelay(1000);
	sata_set_glue_reg(regbase, SATA_CTL, P0_IRST_HARD_TXRX);
	sata_set_glue_reg(regbase, SATA_CTL, P0_IRST_HARD_SYNTH);
	sata_set_glue_reg(regbase, SATA_CTL, P1_IRST_HARD_TXRX);
	sata_set_glue_reg(regbase, SATA_CTL, P1_IRST_HARD_SYNTH);
	udelay(300);

	/* Override reset in serial PHY mode */
	sata_set_glue_reg(regbase, CR_REG_TIMER, CR_TIME_SCALE);
	/* Set reset SATA */
	sata_set_glue_reg(regbase, SATA_CTL, SATA_RST_N);
	sata_set_glue_reg(regbase, SATA_CTL, M_CSYSREQ);
	sata_set_glue_reg(regbase, SATA_CTL, S_CSYSREQ);

	pr_debug("Waiting for PHYs to come up.\n");
	n = 10000;
	do {
		reg_val = nlm_read_sata_reg(regbase, SATA_STATUS);
		if ((reg_val & P1_PHY_READY) && (reg_val & P0_PHY_READY))
			break;
		udelay(10);
	} while (--n > 0);

	if (reg_val  & P0_PHY_READY)
		pr_info("PHY0 is up.\n");
	else
		pr_info("PHY0 is down.\n");
	if (reg_val  & P1_PHY_READY)
		pr_info("PHY1 is up.\n");
	else
		pr_info("PHY1 is down.\n");

	pr_info("XLP AHCI Init Done.\n");
}