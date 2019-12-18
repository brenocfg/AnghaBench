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
struct ufs_mtk_phy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDR_ISO_EN ; 
 int /*<<< orphan*/  CDR_PWR_ON ; 
 int /*<<< orphan*/  FRC_CDR_ISO_EN ; 
 int /*<<< orphan*/  FRC_CDR_PWR_ON ; 
 int /*<<< orphan*/  FRC_FRC_PWR_ON ; 
 int /*<<< orphan*/  FRC_PLL_ISO_EN ; 
 int /*<<< orphan*/  FRC_RX_SQ_EN ; 
 int /*<<< orphan*/  FSM_DIFZ_FRC ; 
 int /*<<< orphan*/  MP_GLB_DIG_8C ; 
 int /*<<< orphan*/  MP_LN_DIG_RX_9C ; 
 int /*<<< orphan*/  MP_LN_DIG_RX_AC ; 
 int /*<<< orphan*/  MP_LN_RX_44 ; 
 int /*<<< orphan*/  PLL_ISO_EN ; 
 int /*<<< orphan*/  PLL_PWR_ON ; 
 int /*<<< orphan*/  RX_SQ_EN ; 
 int /*<<< orphan*/  mphy_clr_bit (struct ufs_mtk_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mphy_set_bit (struct ufs_mtk_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void ufs_mtk_phy_set_active(struct ufs_mtk_phy *phy)
{
	/* release DA_MP_PLL_PWR_ON */
	mphy_set_bit(phy, MP_GLB_DIG_8C, PLL_PWR_ON);
	mphy_clr_bit(phy, MP_GLB_DIG_8C, FRC_FRC_PWR_ON);

	/* release DA_MP_PLL_ISO_EN */
	mphy_clr_bit(phy, MP_GLB_DIG_8C, PLL_ISO_EN);
	mphy_clr_bit(phy, MP_GLB_DIG_8C, FRC_PLL_ISO_EN);

	/* release DA_MP_CDR_PWR_ON */
	mphy_set_bit(phy, MP_LN_RX_44, CDR_PWR_ON);
	mphy_clr_bit(phy, MP_LN_RX_44, FRC_CDR_PWR_ON);

	/* release DA_MP_CDR_ISO_EN */
	mphy_clr_bit(phy, MP_LN_RX_44, CDR_ISO_EN);
	mphy_clr_bit(phy, MP_LN_RX_44, FRC_CDR_ISO_EN);

	/* release DA_MP_RX0_SQ_EN */
	mphy_set_bit(phy, MP_LN_DIG_RX_AC, RX_SQ_EN);
	mphy_clr_bit(phy, MP_LN_DIG_RX_AC, FRC_RX_SQ_EN);

	/* delay 1us to wait DIFZ stable */
	udelay(1);

	/* release DIFZ */
	mphy_clr_bit(phy, MP_LN_DIG_RX_9C, FSM_DIFZ_FRC);
}