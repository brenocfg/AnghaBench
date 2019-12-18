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
struct sun4i_tcon {int /*<<< orphan*/  regs; } ;
struct drm_encoder {scalar_t__ encoder_type; } ;

/* Variables and functions */
 scalar_t__ DRM_MODE_ENCODER_TVDAC ; 
 int /*<<< orphan*/  SUN4I_TCON_MUX_CTRL_REG ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sun5i_a13_tcon_set_mux(struct sun4i_tcon *tcon,
				  const struct drm_encoder *encoder)
{
	u32 val;

	if (encoder->encoder_type == DRM_MODE_ENCODER_TVDAC)
		val = 1;
	else
		val = 0;

	/*
	 * FIXME: Undocumented bits
	 */
	return regmap_write(tcon->regs, SUN4I_TCON_MUX_CTRL_REG, val);
}