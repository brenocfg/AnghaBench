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
typedef  int /*<<< orphan*/  u8 ;
struct sun6i_dphy {int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  GENMASK (unsigned int,int /*<<< orphan*/ ) ; 
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
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

int sun6i_dphy_power_on(struct sun6i_dphy *dphy, unsigned int lanes)
{
	u8 lanes_mask = GENMASK(lanes - 1, 0);

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