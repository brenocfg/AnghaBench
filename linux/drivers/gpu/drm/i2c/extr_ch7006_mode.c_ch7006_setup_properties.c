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
typedef  int uint8_t ;
typedef  int uint64_t ;
struct i2c_client {int dummy; } ;
struct drm_encoder {int dummy; } ;
struct drm_display_mode {int vtotal; int hdisplay; int vdisplay; } ;
struct ch7006_tv_norm_info {int vtotal; int hvirtual; int vdisplay; int voffset; } ;
struct ch7006_state {int* regs; } ;
struct ch7006_priv {size_t norm; int hmargin; int vmargin; int /*<<< orphan*/  contrast; int /*<<< orphan*/  flicker; struct ch7006_mode* mode; struct ch7006_state state; } ;
struct ch7006_mode {int enc_hdisp; int enc_vdisp; struct drm_display_mode mode; } ;

/* Variables and functions */
 size_t CH7006_CONTRAST ; 
 int /*<<< orphan*/  CH7006_CONTRAST_0 ; 
 size_t CH7006_FFILTER ; 
 int /*<<< orphan*/  CH7006_FFILTER_CHROMA ; 
 int /*<<< orphan*/  CH7006_FFILTER_LUMA ; 
 int /*<<< orphan*/  CH7006_FFILTER_TEXT ; 
 int /*<<< orphan*/  CH7006_HPOS ; 
 int /*<<< orphan*/  CH7006_POV ; 
 int /*<<< orphan*/  CH7006_VPOS ; 
 int /*<<< orphan*/  HPOS_8 ; 
 int /*<<< orphan*/  VPOS_8 ; 
 int bitf (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ch7006_dbg (struct i2c_client*,char*,int,int) ; 
 struct ch7006_tv_norm_info* ch7006_tv_norms ; 
 int /*<<< orphan*/  do_div (int,int) ; 
 struct i2c_client* drm_i2c_encoder_get_client (struct drm_encoder*) ; 
 int fixed1 ; 
 int interpolate (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int max (int /*<<< orphan*/ ,int) ; 
 int round_fixed (int) ; 
 int /*<<< orphan*/  setbitf (struct ch7006_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct ch7006_priv* to_ch7006_priv (struct drm_encoder*) ; 

void ch7006_setup_properties(struct drm_encoder *encoder)
{
	struct i2c_client *client = drm_i2c_encoder_get_client(encoder);
	struct ch7006_priv *priv = to_ch7006_priv(encoder);
	struct ch7006_state *state = &priv->state;
	const struct ch7006_tv_norm_info *norm = &ch7006_tv_norms[priv->norm];
	const struct ch7006_mode *ch_mode = priv->mode;
	const struct drm_display_mode *mode = &ch_mode->mode;
	uint8_t *regs = state->regs;
	int flicker, contrast, hpos, vpos;
	uint64_t scale, aspect;

	flicker = interpolate(0, 2, 3, priv->flicker);
	regs[CH7006_FFILTER] = bitf(CH7006_FFILTER_TEXT, flicker) |
		bitf(CH7006_FFILTER_LUMA, flicker) |
		bitf(CH7006_FFILTER_CHROMA, 1);

	contrast = interpolate(0, 5, 7, priv->contrast);
	regs[CH7006_CONTRAST] = bitf(CH7006_CONTRAST_0, contrast);

	scale = norm->vtotal*fixed1;
	do_div(scale, mode->vtotal);

	aspect = ch_mode->enc_hdisp*fixed1;
	do_div(aspect, ch_mode->enc_vdisp);

	hpos = round_fixed((norm->hvirtual * aspect - mode->hdisplay * scale)
			   * priv->hmargin * mode->vtotal) / norm->vtotal / 100 / 4;

	setbitf(state, CH7006_POV, HPOS_8, hpos);
	setbitf(state, CH7006_HPOS, 0, hpos);

	vpos = max(0, norm->vdisplay - round_fixed(mode->vdisplay*scale)
		   + norm->voffset) * priv->vmargin / 100 / 2;

	setbitf(state, CH7006_POV, VPOS_8, vpos);
	setbitf(state, CH7006_VPOS, 0, vpos);

	ch7006_dbg(client, "hpos: %d, vpos: %d\n", hpos, vpos);
}