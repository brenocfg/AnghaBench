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
typedef  int u16 ;
struct brcms_phy {TYPE_1__* sh; } ;
struct TYPE_2__ {int /*<<< orphan*/  physhim; } ;

/* Variables and functions */
 int BBCFG_RESETCCA ; 
 int /*<<< orphan*/  NPHY_RFSEQ_RESET2RX ; 
 int /*<<< orphan*/  OFF ; 
 int /*<<< orphan*/  ON ; 
 int read_phy_reg (struct brcms_phy*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  wlapi_bmac_phyclk_fgc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlc_phy_force_rfseq_nphy (struct brcms_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_phy_reg (struct brcms_phy*,int,int) ; 

__attribute__((used)) static void wlc_phy_resetcca_nphy(struct brcms_phy *pi)
{
	u16 val;

	wlapi_bmac_phyclk_fgc(pi->sh->physhim, ON);

	val = read_phy_reg(pi, 0x01);
	write_phy_reg(pi, 0x01, val | BBCFG_RESETCCA);
	udelay(1);
	write_phy_reg(pi, 0x01, val & (~BBCFG_RESETCCA));

	wlapi_bmac_phyclk_fgc(pi->sh->physhim, OFF);

	wlc_phy_force_rfseq_nphy(pi, NPHY_RFSEQ_RESET2RX);
}