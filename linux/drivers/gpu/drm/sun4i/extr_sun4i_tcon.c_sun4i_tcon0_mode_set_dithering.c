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
typedef  int u32 ;
struct sun4i_tcon {int /*<<< orphan*/  regs; } ;
struct TYPE_2__ {int bpc; int num_bus_formats; int* bus_formats; } ;
struct drm_connector {TYPE_1__ display_info; } ;

/* Variables and functions */
#define  MEDIA_BUS_FMT_RGB565_1X16 130 
#define  MEDIA_BUS_FMT_RGB666_1X18 129 
#define  MEDIA_BUS_FMT_RGB666_1X7X3_SPWG 128 
 int SUN4I_TCON0_FRM_CTL_EN ; 
 int SUN4I_TCON0_FRM_CTL_MODE_B ; 
 int SUN4I_TCON0_FRM_CTL_MODE_R ; 
 int /*<<< orphan*/  SUN4I_TCON0_FRM_SEED_LB_REG ; 
 int /*<<< orphan*/  SUN4I_TCON0_FRM_SEED_LG_REG ; 
 int /*<<< orphan*/  SUN4I_TCON0_FRM_SEED_LR_REG ; 
 int /*<<< orphan*/  SUN4I_TCON0_FRM_SEED_PB_REG ; 
 int /*<<< orphan*/  SUN4I_TCON0_FRM_SEED_PG_REG ; 
 int /*<<< orphan*/  SUN4I_TCON0_FRM_SEED_PR_REG ; 
 int /*<<< orphan*/  SUN4I_TCON0_FRM_TBL0_REG ; 
 int /*<<< orphan*/  SUN4I_TCON0_FRM_TBL1_REG ; 
 int /*<<< orphan*/  SUN4I_TCON0_FRM_TBL2_REG ; 
 int /*<<< orphan*/  SUN4I_TCON0_FRM_TBL3_REG ; 
 int /*<<< orphan*/  SUN4I_TCON_FRM_CTL_REG ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sun4i_tcon0_mode_set_dithering(struct sun4i_tcon *tcon,
					   const struct drm_connector *connector)
{
	u32 bus_format = 0;
	u32 val = 0;

	/* XXX Would this ever happen? */
	if (!connector)
		return;

	/*
	 * FIXME: Undocumented bits
	 *
	 * The whole dithering process and these parameters are not
	 * explained in the vendor documents or BSP kernel code.
	 */
	regmap_write(tcon->regs, SUN4I_TCON0_FRM_SEED_PR_REG, 0x11111111);
	regmap_write(tcon->regs, SUN4I_TCON0_FRM_SEED_PG_REG, 0x11111111);
	regmap_write(tcon->regs, SUN4I_TCON0_FRM_SEED_PB_REG, 0x11111111);
	regmap_write(tcon->regs, SUN4I_TCON0_FRM_SEED_LR_REG, 0x11111111);
	regmap_write(tcon->regs, SUN4I_TCON0_FRM_SEED_LG_REG, 0x11111111);
	regmap_write(tcon->regs, SUN4I_TCON0_FRM_SEED_LB_REG, 0x11111111);
	regmap_write(tcon->regs, SUN4I_TCON0_FRM_TBL0_REG, 0x01010000);
	regmap_write(tcon->regs, SUN4I_TCON0_FRM_TBL1_REG, 0x15151111);
	regmap_write(tcon->regs, SUN4I_TCON0_FRM_TBL2_REG, 0x57575555);
	regmap_write(tcon->regs, SUN4I_TCON0_FRM_TBL3_REG, 0x7f7f7777);

	/* Do dithering if panel only supports 6 bits per color */
	if (connector->display_info.bpc == 6)
		val |= SUN4I_TCON0_FRM_CTL_EN;

	if (connector->display_info.num_bus_formats == 1)
		bus_format = connector->display_info.bus_formats[0];

	/* Check the connection format */
	switch (bus_format) {
	case MEDIA_BUS_FMT_RGB565_1X16:
		/* R and B components are only 5 bits deep */
		val |= SUN4I_TCON0_FRM_CTL_MODE_R;
		val |= SUN4I_TCON0_FRM_CTL_MODE_B;
		/* Fall through */
	case MEDIA_BUS_FMT_RGB666_1X18:
	case MEDIA_BUS_FMT_RGB666_1X7X3_SPWG:
		/* Fall through: enable dithering */
		val |= SUN4I_TCON0_FRM_CTL_EN;
		break;
	}

	/* Write dithering settings */
	regmap_write(tcon->regs, SUN4I_TCON_FRM_CTL_REG, val);
}