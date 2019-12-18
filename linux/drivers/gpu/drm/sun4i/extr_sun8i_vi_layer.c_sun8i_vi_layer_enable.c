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
struct TYPE_2__ {int /*<<< orphan*/  regs; } ;
struct sun8i_mixer {TYPE_1__ engine; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,char*,int,int) ; 
 int /*<<< orphan*/  SUN8I_MIXER_BLEND_PIPE_CTL (int) ; 
 int SUN8I_MIXER_BLEND_PIPE_CTL_EN (unsigned int) ; 
 int /*<<< orphan*/  SUN8I_MIXER_BLEND_ROUTE (int) ; 
 int SUN8I_MIXER_BLEND_ROUTE_PIPE_MSK (unsigned int) ; 
 int SUN8I_MIXER_BLEND_ROUTE_PIPE_SHIFT (unsigned int) ; 
 int /*<<< orphan*/  SUN8I_MIXER_CHAN_VI_LAYER_ATTR (int,int) ; 
 int SUN8I_MIXER_CHAN_VI_LAYER_ATTR_EN ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int sun8i_blender_base (struct sun8i_mixer*) ; 
 int sun8i_channel_base (struct sun8i_mixer*,int) ; 

__attribute__((used)) static void sun8i_vi_layer_enable(struct sun8i_mixer *mixer, int channel,
				  int overlay, bool enable, unsigned int zpos,
				  unsigned int old_zpos)
{
	u32 val, bld_base, ch_base;

	bld_base = sun8i_blender_base(mixer);
	ch_base = sun8i_channel_base(mixer, channel);

	DRM_DEBUG_DRIVER("%sabling VI channel %d overlay %d\n",
			 enable ? "En" : "Dis", channel, overlay);

	if (enable)
		val = SUN8I_MIXER_CHAN_VI_LAYER_ATTR_EN;
	else
		val = 0;

	regmap_update_bits(mixer->engine.regs,
			   SUN8I_MIXER_CHAN_VI_LAYER_ATTR(ch_base, overlay),
			   SUN8I_MIXER_CHAN_VI_LAYER_ATTR_EN, val);

	if (!enable || zpos != old_zpos) {
		regmap_update_bits(mixer->engine.regs,
				   SUN8I_MIXER_BLEND_PIPE_CTL(bld_base),
				   SUN8I_MIXER_BLEND_PIPE_CTL_EN(old_zpos),
				   0);

		regmap_update_bits(mixer->engine.regs,
				   SUN8I_MIXER_BLEND_ROUTE(bld_base),
				   SUN8I_MIXER_BLEND_ROUTE_PIPE_MSK(old_zpos),
				   0);
	}

	if (enable) {
		val = SUN8I_MIXER_BLEND_PIPE_CTL_EN(zpos);

		regmap_update_bits(mixer->engine.regs,
				   SUN8I_MIXER_BLEND_PIPE_CTL(bld_base),
				   val, val);

		val = channel << SUN8I_MIXER_BLEND_ROUTE_PIPE_SHIFT(zpos);

		regmap_update_bits(mixer->engine.regs,
				   SUN8I_MIXER_BLEND_ROUTE(bld_base),
				   SUN8I_MIXER_BLEND_ROUTE_PIPE_MSK(zpos),
				   val);
	}
}