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
struct sun4i_tcon {int id; int /*<<< orphan*/  regs; } ;
struct drm_encoder {int encoder_type; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  DRM_MODE_ENCODER_TMDS 128 
 int EINVAL ; 
 int /*<<< orphan*/  SUN4I_TCON_MUX_CTRL_REG ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct sun4i_tcon* sun4i_get_tcon0 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sun6i_tcon_set_mux(struct sun4i_tcon *tcon,
			      const struct drm_encoder *encoder)
{
	struct sun4i_tcon *tcon0 = sun4i_get_tcon0(encoder->dev);
	u32 shift;

	if (!tcon0)
		return -EINVAL;

	switch (encoder->encoder_type) {
	case DRM_MODE_ENCODER_TMDS:
		/* HDMI */
		shift = 8;
		break;
	default:
		/* TODO A31 has MIPI DSI but A31s does not */
		return -EINVAL;
	}

	regmap_update_bits(tcon0->regs, SUN4I_TCON_MUX_CTRL_REG,
			   0x3 << shift, tcon->id << shift);

	return 0;
}