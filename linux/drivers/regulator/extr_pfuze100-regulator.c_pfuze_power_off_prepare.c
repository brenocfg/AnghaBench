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
struct TYPE_2__ {int /*<<< orphan*/  regmap; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PFUZE100_SW1ABMODE ; 
 int /*<<< orphan*/  PFUZE100_SW1CMODE ; 
 int /*<<< orphan*/  PFUZE100_SW2MODE ; 
 int /*<<< orphan*/  PFUZE100_SW3AMODE ; 
 int /*<<< orphan*/  PFUZE100_SW3BMODE ; 
 int /*<<< orphan*/  PFUZE100_SW4MODE ; 
 int PFUZE100_SWxMODE_APS_OFF ; 
 int PFUZE100_SWxMODE_MASK ; 
 int /*<<< orphan*/  PFUZE100_VGEN1VOL ; 
 int /*<<< orphan*/  PFUZE100_VGEN2VOL ; 
 int /*<<< orphan*/  PFUZE100_VGEN3VOL ; 
 int /*<<< orphan*/  PFUZE100_VGEN4VOL ; 
 int /*<<< orphan*/  PFUZE100_VGEN5VOL ; 
 int /*<<< orphan*/  PFUZE100_VGEN6VOL ; 
 int PFUZE100_VGENxLPWR ; 
 int PFUZE100_VGENxSTBY ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 TYPE_1__* syspm_pfuze_chip ; 

__attribute__((used)) static void pfuze_power_off_prepare(void)
{
	dev_info(syspm_pfuze_chip->dev, "Configure standby mode for power off");

	/* Switch from default mode: APS/APS to APS/Off */
	regmap_update_bits(syspm_pfuze_chip->regmap, PFUZE100_SW1ABMODE,
			   PFUZE100_SWxMODE_MASK, PFUZE100_SWxMODE_APS_OFF);
	regmap_update_bits(syspm_pfuze_chip->regmap, PFUZE100_SW1CMODE,
			   PFUZE100_SWxMODE_MASK, PFUZE100_SWxMODE_APS_OFF);
	regmap_update_bits(syspm_pfuze_chip->regmap, PFUZE100_SW2MODE,
			   PFUZE100_SWxMODE_MASK, PFUZE100_SWxMODE_APS_OFF);
	regmap_update_bits(syspm_pfuze_chip->regmap, PFUZE100_SW3AMODE,
			   PFUZE100_SWxMODE_MASK, PFUZE100_SWxMODE_APS_OFF);
	regmap_update_bits(syspm_pfuze_chip->regmap, PFUZE100_SW3BMODE,
			   PFUZE100_SWxMODE_MASK, PFUZE100_SWxMODE_APS_OFF);
	regmap_update_bits(syspm_pfuze_chip->regmap, PFUZE100_SW4MODE,
			   PFUZE100_SWxMODE_MASK, PFUZE100_SWxMODE_APS_OFF);

	regmap_update_bits(syspm_pfuze_chip->regmap, PFUZE100_VGEN1VOL,
			   PFUZE100_VGENxLPWR | PFUZE100_VGENxSTBY,
			   PFUZE100_VGENxSTBY);
	regmap_update_bits(syspm_pfuze_chip->regmap, PFUZE100_VGEN2VOL,
			   PFUZE100_VGENxLPWR | PFUZE100_VGENxSTBY,
			   PFUZE100_VGENxSTBY);
	regmap_update_bits(syspm_pfuze_chip->regmap, PFUZE100_VGEN3VOL,
			   PFUZE100_VGENxLPWR | PFUZE100_VGENxSTBY,
			   PFUZE100_VGENxSTBY);
	regmap_update_bits(syspm_pfuze_chip->regmap, PFUZE100_VGEN4VOL,
			   PFUZE100_VGENxLPWR | PFUZE100_VGENxSTBY,
			   PFUZE100_VGENxSTBY);
	regmap_update_bits(syspm_pfuze_chip->regmap, PFUZE100_VGEN5VOL,
			   PFUZE100_VGENxLPWR | PFUZE100_VGENxSTBY,
			   PFUZE100_VGENxSTBY);
	regmap_update_bits(syspm_pfuze_chip->regmap, PFUZE100_VGEN6VOL,
			   PFUZE100_VGENxLPWR | PFUZE100_VGENxSTBY,
			   PFUZE100_VGENxSTBY);
}