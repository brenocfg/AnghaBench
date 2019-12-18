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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {scalar_t__ lanes; } ;
struct sun6i_dphy {int /*<<< orphan*/  regs; TYPE_1__ config; } ;
struct phy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GENMASK (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUN6I_DPHY_ANA0_REG ; 
 int SUN6I_DPHY_ANA0_REG_DEN (int /*<<< orphan*/ ) ; 
 int SUN6I_DPHY_ANA0_REG_DMPC ; 
 int SUN6I_DPHY_ANA0_REG_DMPD (int /*<<< orphan*/ ) ; 
 int SUN6I_DPHY_ANA0_REG_PWS ; 
 int SUN6I_DPHY_ANA0_REG_SLV (int) ; 
 int /*<<< orphan*/  SUN6I_DPHY_ANA1_REG ; 
 int SUN6I_DPHY_ANA1_REG_CSMPS (int) ; 
 int SUN6I_DPHY_ANA1_REG_SVTT (int) ; 
 int SUN6I_DPHY_ANA1_REG_VTTMODE ; 
 int SUN6I_DPHY_ANA2_EN_CK_CPU ; 
 int SUN6I_DPHY_ANA2_EN_P2S_CPU (int /*<<< orphan*/ ) ; 
 int SUN6I_DPHY_ANA2_EN_P2S_CPU_MASK ; 
 int /*<<< orphan*/  SUN6I_DPHY_ANA2_REG ; 
 int SUN6I_DPHY_ANA2_REG_ENIB ; 
 int SUN6I_DPHY_ANA3_EN_DIV ; 
 int SUN6I_DPHY_ANA3_EN_LDOC ; 
 int SUN6I_DPHY_ANA3_EN_LDOD ; 
 int SUN6I_DPHY_ANA3_EN_LDOR ; 
 int SUN6I_DPHY_ANA3_EN_VTTC ; 
 int SUN6I_DPHY_ANA3_EN_VTTD (int /*<<< orphan*/ ) ; 
 int SUN6I_DPHY_ANA3_EN_VTTD_MASK ; 
 int /*<<< orphan*/  SUN6I_DPHY_ANA3_REG ; 
 int /*<<< orphan*/  SUN6I_DPHY_ANA4_REG ; 
 int SUN6I_DPHY_ANA4_REG_CKDV (int) ; 
 int SUN6I_DPHY_ANA4_REG_DMPLVC ; 
 int SUN6I_DPHY_ANA4_REG_DMPLVD (int /*<<< orphan*/ ) ; 
 int SUN6I_DPHY_ANA4_REG_TMSC (int) ; 
 int SUN6I_DPHY_ANA4_REG_TMSD (int) ; 
 int SUN6I_DPHY_ANA4_REG_TXDNSC (int) ; 
 int SUN6I_DPHY_ANA4_REG_TXDNSD (int) ; 
 int SUN6I_DPHY_ANA4_REG_TXPUSC (int) ; 
 int SUN6I_DPHY_ANA4_REG_TXPUSD (int) ; 
 int SUN6I_DPHY_GCTL_EN ; 
 int SUN6I_DPHY_GCTL_LANE_NUM (scalar_t__) ; 
 int /*<<< orphan*/  SUN6I_DPHY_GCTL_REG ; 
 int SUN6I_DPHY_TX_CTL_HS_TX_CLK_CONT ; 
 int /*<<< orphan*/  SUN6I_DPHY_TX_CTL_REG ; 
 int SUN6I_DPHY_TX_TIME0_HS_PREPARE (int) ; 
 int SUN6I_DPHY_TX_TIME0_HS_TRAIL (int) ; 
 int SUN6I_DPHY_TX_TIME0_LP_CLK_DIV (int) ; 
 int /*<<< orphan*/  SUN6I_DPHY_TX_TIME0_REG ; 
 int SUN6I_DPHY_TX_TIME1_CLK_POST (int) ; 
 int SUN6I_DPHY_TX_TIME1_CLK_PRE (int) ; 
 int SUN6I_DPHY_TX_TIME1_CLK_PREPARE (int) ; 
 int SUN6I_DPHY_TX_TIME1_CLK_ZERO (int) ; 
 int /*<<< orphan*/  SUN6I_DPHY_TX_TIME1_REG ; 
 int SUN6I_DPHY_TX_TIME2_CLK_TRAIL (int) ; 
 int /*<<< orphan*/  SUN6I_DPHY_TX_TIME2_REG ; 
 int /*<<< orphan*/  SUN6I_DPHY_TX_TIME3_REG ; 
 int SUN6I_DPHY_TX_TIME4_HS_TX_ANA0 (int) ; 
 int SUN6I_DPHY_TX_TIME4_HS_TX_ANA1 (int) ; 
 int /*<<< orphan*/  SUN6I_DPHY_TX_TIME4_REG ; 
 struct sun6i_dphy* phy_get_drvdata (struct phy*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int sun6i_dphy_power_on(struct phy *phy)
{
	struct sun6i_dphy *dphy = phy_get_drvdata(phy);
	u8 lanes_mask = GENMASK(dphy->config.lanes - 1, 0);

	regmap_write(dphy->regs, SUN6I_DPHY_TX_CTL_REG,
		     SUN6I_DPHY_TX_CTL_HS_TX_CLK_CONT);

	regmap_write(dphy->regs, SUN6I_DPHY_TX_TIME0_REG,
		     SUN6I_DPHY_TX_TIME0_LP_CLK_DIV(14) |
		     SUN6I_DPHY_TX_TIME0_HS_PREPARE(6) |
		     SUN6I_DPHY_TX_TIME0_HS_TRAIL(10));

	regmap_write(dphy->regs, SUN6I_DPHY_TX_TIME1_REG,
		     SUN6I_DPHY_TX_TIME1_CLK_PREPARE(7) |
		     SUN6I_DPHY_TX_TIME1_CLK_ZERO(50) |
		     SUN6I_DPHY_TX_TIME1_CLK_PRE(3) |
		     SUN6I_DPHY_TX_TIME1_CLK_POST(10));

	regmap_write(dphy->regs, SUN6I_DPHY_TX_TIME2_REG,
		     SUN6I_DPHY_TX_TIME2_CLK_TRAIL(30));

	regmap_write(dphy->regs, SUN6I_DPHY_TX_TIME3_REG, 0);

	regmap_write(dphy->regs, SUN6I_DPHY_TX_TIME4_REG,
		     SUN6I_DPHY_TX_TIME4_HS_TX_ANA0(3) |
		     SUN6I_DPHY_TX_TIME4_HS_TX_ANA1(3));

	regmap_write(dphy->regs, SUN6I_DPHY_GCTL_REG,
		     SUN6I_DPHY_GCTL_LANE_NUM(dphy->config.lanes) |
		     SUN6I_DPHY_GCTL_EN);

	regmap_write(dphy->regs, SUN6I_DPHY_ANA0_REG,
		     SUN6I_DPHY_ANA0_REG_PWS |
		     SUN6I_DPHY_ANA0_REG_DMPC |
		     SUN6I_DPHY_ANA0_REG_SLV(7) |
		     SUN6I_DPHY_ANA0_REG_DMPD(lanes_mask) |
		     SUN6I_DPHY_ANA0_REG_DEN(lanes_mask));

	regmap_write(dphy->regs, SUN6I_DPHY_ANA1_REG,
		     SUN6I_DPHY_ANA1_REG_CSMPS(1) |
		     SUN6I_DPHY_ANA1_REG_SVTT(7));

	regmap_write(dphy->regs, SUN6I_DPHY_ANA4_REG,
		     SUN6I_DPHY_ANA4_REG_CKDV(1) |
		     SUN6I_DPHY_ANA4_REG_TMSC(1) |
		     SUN6I_DPHY_ANA4_REG_TMSD(1) |
		     SUN6I_DPHY_ANA4_REG_TXDNSC(1) |
		     SUN6I_DPHY_ANA4_REG_TXDNSD(1) |
		     SUN6I_DPHY_ANA4_REG_TXPUSC(1) |
		     SUN6I_DPHY_ANA4_REG_TXPUSD(1) |
		     SUN6I_DPHY_ANA4_REG_DMPLVC |
		     SUN6I_DPHY_ANA4_REG_DMPLVD(lanes_mask));

	regmap_write(dphy->regs, SUN6I_DPHY_ANA2_REG,
		     SUN6I_DPHY_ANA2_REG_ENIB);
	udelay(5);

	regmap_write(dphy->regs, SUN6I_DPHY_ANA3_REG,
		     SUN6I_DPHY_ANA3_EN_LDOR |
		     SUN6I_DPHY_ANA3_EN_LDOC |
		     SUN6I_DPHY_ANA3_EN_LDOD);
	udelay(1);

	regmap_update_bits(dphy->regs, SUN6I_DPHY_ANA3_REG,
			   SUN6I_DPHY_ANA3_EN_VTTC |
			   SUN6I_DPHY_ANA3_EN_VTTD_MASK,
			   SUN6I_DPHY_ANA3_EN_VTTC |
			   SUN6I_DPHY_ANA3_EN_VTTD(lanes_mask));
	udelay(1);

	regmap_update_bits(dphy->regs, SUN6I_DPHY_ANA3_REG,
			   SUN6I_DPHY_ANA3_EN_DIV,
			   SUN6I_DPHY_ANA3_EN_DIV);
	udelay(1);

	regmap_update_bits(dphy->regs, SUN6I_DPHY_ANA2_REG,
			   SUN6I_DPHY_ANA2_EN_CK_CPU,
			   SUN6I_DPHY_ANA2_EN_CK_CPU);
	udelay(1);

	regmap_update_bits(dphy->regs, SUN6I_DPHY_ANA1_REG,
			   SUN6I_DPHY_ANA1_REG_VTTMODE,
			   SUN6I_DPHY_ANA1_REG_VTTMODE);

	regmap_update_bits(dphy->regs, SUN6I_DPHY_ANA2_REG,
			   SUN6I_DPHY_ANA2_EN_P2S_CPU_MASK,
			   SUN6I_DPHY_ANA2_EN_P2S_CPU(lanes_mask));

	return 0;
}