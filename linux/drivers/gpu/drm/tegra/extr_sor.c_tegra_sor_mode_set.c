#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct tegra_sor_state {int bpc; } ;
struct TYPE_5__ {int /*<<< orphan*/  crtc; } ;
struct TYPE_6__ {TYPE_1__ encoder; } ;
struct tegra_sor {TYPE_4__* soc; TYPE_2__ output; } ;
struct tegra_dc {scalar_t__ pipe; } ;
struct drm_display_mode {int flags; int vtotal; int htotal; int vsync_end; int vsync_start; int hsync_end; int hsync_start; unsigned int vdisplay; unsigned int hdisplay; } ;
struct TYPE_8__ {TYPE_3__* regs; } ;
struct TYPE_7__ {scalar_t__ head_state5; scalar_t__ head_state4; scalar_t__ head_state3; scalar_t__ head_state2; scalar_t__ head_state1; } ;

/* Variables and functions */
 int DRM_MODE_FLAG_NHSYNC ; 
 int DRM_MODE_FLAG_NVSYNC ; 
 int DRM_MODE_FLAG_PHSYNC ; 
 int DRM_MODE_FLAG_PVSYNC ; 
 scalar_t__ SOR_STATE1 ; 
 int SOR_STATE_ASY_CRC_MODE_COMPLETE ; 
 int SOR_STATE_ASY_CRC_MODE_MASK ; 
 int SOR_STATE_ASY_HSYNCPOL ; 
 int SOR_STATE_ASY_OWNER (scalar_t__) ; 
 int SOR_STATE_ASY_OWNER_MASK ; 
 int SOR_STATE_ASY_PIXELDEPTH_BPP_18_444 ; 
 int SOR_STATE_ASY_PIXELDEPTH_BPP_24_444 ; 
 int SOR_STATE_ASY_PIXELDEPTH_BPP_30_444 ; 
 int SOR_STATE_ASY_PIXELDEPTH_BPP_36_444 ; 
 int SOR_STATE_ASY_PIXELDEPTH_BPP_48_444 ; 
 int SOR_STATE_ASY_PIXELDEPTH_MASK ; 
 int SOR_STATE_ASY_VSYNCPOL ; 
 int tegra_sor_readl (struct tegra_sor*,scalar_t__) ; 
 int /*<<< orphan*/  tegra_sor_writel (struct tegra_sor*,int,scalar_t__) ; 
 struct tegra_dc* to_tegra_dc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tegra_sor_mode_set(struct tegra_sor *sor,
			       const struct drm_display_mode *mode,
			       struct tegra_sor_state *state)
{
	struct tegra_dc *dc = to_tegra_dc(sor->output.encoder.crtc);
	unsigned int vbe, vse, hbe, hse, vbs, hbs;
	u32 value;

	value = tegra_sor_readl(sor, SOR_STATE1);
	value &= ~SOR_STATE_ASY_PIXELDEPTH_MASK;
	value &= ~SOR_STATE_ASY_CRC_MODE_MASK;
	value &= ~SOR_STATE_ASY_OWNER_MASK;

	value |= SOR_STATE_ASY_CRC_MODE_COMPLETE |
		 SOR_STATE_ASY_OWNER(dc->pipe + 1);

	if (mode->flags & DRM_MODE_FLAG_PHSYNC)
		value &= ~SOR_STATE_ASY_HSYNCPOL;

	if (mode->flags & DRM_MODE_FLAG_NHSYNC)
		value |= SOR_STATE_ASY_HSYNCPOL;

	if (mode->flags & DRM_MODE_FLAG_PVSYNC)
		value &= ~SOR_STATE_ASY_VSYNCPOL;

	if (mode->flags & DRM_MODE_FLAG_NVSYNC)
		value |= SOR_STATE_ASY_VSYNCPOL;

	switch (state->bpc) {
	case 16:
		value |= SOR_STATE_ASY_PIXELDEPTH_BPP_48_444;
		break;

	case 12:
		value |= SOR_STATE_ASY_PIXELDEPTH_BPP_36_444;
		break;

	case 10:
		value |= SOR_STATE_ASY_PIXELDEPTH_BPP_30_444;
		break;

	case 8:
		value |= SOR_STATE_ASY_PIXELDEPTH_BPP_24_444;
		break;

	case 6:
		value |= SOR_STATE_ASY_PIXELDEPTH_BPP_18_444;
		break;

	default:
		value |= SOR_STATE_ASY_PIXELDEPTH_BPP_24_444;
		break;
	}

	tegra_sor_writel(sor, value, SOR_STATE1);

	/*
	 * TODO: The video timing programming below doesn't seem to match the
	 * register definitions.
	 */

	value = ((mode->vtotal & 0x7fff) << 16) | (mode->htotal & 0x7fff);
	tegra_sor_writel(sor, value, sor->soc->regs->head_state1 + dc->pipe);

	/* sync end = sync width - 1 */
	vse = mode->vsync_end - mode->vsync_start - 1;
	hse = mode->hsync_end - mode->hsync_start - 1;

	value = ((vse & 0x7fff) << 16) | (hse & 0x7fff);
	tegra_sor_writel(sor, value, sor->soc->regs->head_state2 + dc->pipe);

	/* blank end = sync end + back porch */
	vbe = vse + (mode->vtotal - mode->vsync_end);
	hbe = hse + (mode->htotal - mode->hsync_end);

	value = ((vbe & 0x7fff) << 16) | (hbe & 0x7fff);
	tegra_sor_writel(sor, value, sor->soc->regs->head_state3 + dc->pipe);

	/* blank start = blank end + active */
	vbs = vbe + mode->vdisplay;
	hbs = hbe + mode->hdisplay;

	value = ((vbs & 0x7fff) << 16) | (hbs & 0x7fff);
	tegra_sor_writel(sor, value, sor->soc->regs->head_state4 + dc->pipe);

	/* XXX interlacing support */
	tegra_sor_writel(sor, 0x001, sor->soc->regs->head_state5 + dc->pipe);
}