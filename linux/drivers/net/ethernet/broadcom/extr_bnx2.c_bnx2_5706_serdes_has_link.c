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
typedef  int u32 ;
struct bnx2 {int phy_flags; } ;

/* Variables and functions */
 int BNX2_PHY_FLAG_NO_PARALLEL ; 
 int /*<<< orphan*/  MII_BNX2_DSP_ADDRESS ; 
 int /*<<< orphan*/  MII_BNX2_DSP_RW_PORT ; 
 int /*<<< orphan*/  MII_BNX2_MISC_SHADOW ; 
 int /*<<< orphan*/  MII_EXPAND_REG1 ; 
 int MII_EXPAND_REG1_RUDI_C ; 
 int /*<<< orphan*/  MISC_SHDW_AN_DBG ; 
 int MISC_SHDW_AN_DBG_NOSYNC ; 
 int MISC_SHDW_AN_DBG_RUDI_INVALID ; 
 int /*<<< orphan*/  MISC_SHDW_MODE_CTL ; 
 int MISC_SHDW_MODE_CTL_SIG_DET ; 
 int /*<<< orphan*/  bnx2_read_phy (struct bnx2*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  bnx2_write_phy (struct bnx2*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bnx2_5706_serdes_has_link(struct bnx2 *bp)
{
	u32 mode_ctl, an_dbg, exp;

	if (bp->phy_flags & BNX2_PHY_FLAG_NO_PARALLEL)
		return 0;

	bnx2_write_phy(bp, MII_BNX2_MISC_SHADOW, MISC_SHDW_MODE_CTL);
	bnx2_read_phy(bp, MII_BNX2_MISC_SHADOW, &mode_ctl);

	if (!(mode_ctl & MISC_SHDW_MODE_CTL_SIG_DET))
		return 0;

	bnx2_write_phy(bp, MII_BNX2_MISC_SHADOW, MISC_SHDW_AN_DBG);
	bnx2_read_phy(bp, MII_BNX2_MISC_SHADOW, &an_dbg);
	bnx2_read_phy(bp, MII_BNX2_MISC_SHADOW, &an_dbg);

	if (an_dbg & (MISC_SHDW_AN_DBG_NOSYNC | MISC_SHDW_AN_DBG_RUDI_INVALID))
		return 0;

	bnx2_write_phy(bp, MII_BNX2_DSP_ADDRESS, MII_EXPAND_REG1);
	bnx2_read_phy(bp, MII_BNX2_DSP_RW_PORT, &exp);
	bnx2_read_phy(bp, MII_BNX2_DSP_RW_PORT, &exp);

	if (exp & MII_EXPAND_REG1_RUDI_C)	/* receiving CONFIG */
		return 0;

	return 1;
}