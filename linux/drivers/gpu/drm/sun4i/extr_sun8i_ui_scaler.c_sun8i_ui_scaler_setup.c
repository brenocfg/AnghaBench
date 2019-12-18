#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {int /*<<< orphan*/  regs; } ;
struct sun8i_mixer {TYPE_2__ engine; TYPE_1__* cfg; } ;
struct TYPE_3__ {int vi_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  SUN8I_SCALER_GSU_HCOEFF (int,int) ; 
 int /*<<< orphan*/  SUN8I_SCALER_GSU_HPHASE (int) ; 
 int /*<<< orphan*/  SUN8I_SCALER_GSU_HSTEP (int) ; 
 int /*<<< orphan*/  SUN8I_SCALER_GSU_INSIZE (int) ; 
 int /*<<< orphan*/  SUN8I_SCALER_GSU_OUTSIZE (int) ; 
 int /*<<< orphan*/  SUN8I_SCALER_GSU_VPHASE (int) ; 
 int /*<<< orphan*/  SUN8I_SCALER_GSU_VSTEP (int) ; 
 int SUN8I_UI_SCALER_COEFF_COUNT ; 
 int SUN8I_UI_SCALER_PHASE_FRAC ; 
 int SUN8I_UI_SCALER_SCALE_FRAC ; 
 int SUN8I_UI_SCALER_SIZE (int,int) ; 
 scalar_t__ WARN_ON (int) ; 
 int* lan2coefftab16 ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int sun8i_ui_scaler_base (struct sun8i_mixer*,int) ; 
 int sun8i_ui_scaler_coef_index (int) ; 

void sun8i_ui_scaler_setup(struct sun8i_mixer *mixer, int layer,
			   u32 src_w, u32 src_h, u32 dst_w, u32 dst_h,
			   u32 hscale, u32 vscale, u32 hphase, u32 vphase)
{
	u32 insize, outsize;
	int i, offset;
	u32 base;

	if (WARN_ON(layer < mixer->cfg->vi_num))
		return;

	base = sun8i_ui_scaler_base(mixer, layer);

	hphase <<= SUN8I_UI_SCALER_PHASE_FRAC - 16;
	vphase <<= SUN8I_UI_SCALER_PHASE_FRAC - 16;
	hscale <<= SUN8I_UI_SCALER_SCALE_FRAC - 16;
	vscale <<= SUN8I_UI_SCALER_SCALE_FRAC - 16;

	insize = SUN8I_UI_SCALER_SIZE(src_w, src_h);
	outsize = SUN8I_UI_SCALER_SIZE(dst_w, dst_h);

	regmap_write(mixer->engine.regs,
		     SUN8I_SCALER_GSU_OUTSIZE(base), outsize);
	regmap_write(mixer->engine.regs,
		     SUN8I_SCALER_GSU_INSIZE(base), insize);
	regmap_write(mixer->engine.regs,
		     SUN8I_SCALER_GSU_HSTEP(base), hscale);
	regmap_write(mixer->engine.regs,
		     SUN8I_SCALER_GSU_VSTEP(base), vscale);
	regmap_write(mixer->engine.regs,
		     SUN8I_SCALER_GSU_HPHASE(base), hphase);
	regmap_write(mixer->engine.regs,
		     SUN8I_SCALER_GSU_VPHASE(base), vphase);
	offset = sun8i_ui_scaler_coef_index(hscale) *
			SUN8I_UI_SCALER_COEFF_COUNT;
	for (i = 0; i < SUN8I_UI_SCALER_COEFF_COUNT; i++)
		regmap_write(mixer->engine.regs,
			     SUN8I_SCALER_GSU_HCOEFF(base, i),
			     lan2coefftab16[offset + i]);
}