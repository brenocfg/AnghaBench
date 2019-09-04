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
struct zx_vou_hw {int vouctl; } ;
struct zx_crtc_bits {int div_vga_shift; int div_pic_shift; int div_tvenc_shift; int div_hdmi_pnx_shift; int div_hdmi_shift; int div_inf_shift; int div_layer_shift; } ;
struct zx_crtc {struct zx_crtc_bits* bits; struct zx_vou_hw* vou; } ;
struct vou_div_config {int id; int val; } ;
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 int DIV_PARA_UPDATE ; 
 int VOU_CLK_SEL ; 
#define  VOU_DIV_HDMI 134 
#define  VOU_DIV_HDMI_PNX 133 
#define  VOU_DIV_INF 132 
#define  VOU_DIV_LAYER 131 
 int VOU_DIV_PARA ; 
#define  VOU_DIV_PIC 130 
#define  VOU_DIV_TVENC 129 
#define  VOU_DIV_VGA 128 
 struct zx_crtc* to_zx_crtc (struct drm_crtc*) ; 
 int /*<<< orphan*/  zx_writel_mask (int,int,int) ; 

void zx_vou_config_dividers(struct drm_crtc *crtc,
			    struct vou_div_config *configs, int num)
{
	struct zx_crtc *zcrtc = to_zx_crtc(crtc);
	struct zx_vou_hw *vou = zcrtc->vou;
	const struct zx_crtc_bits *bits = zcrtc->bits;
	int i;

	/* Clear update flag bit */
	zx_writel_mask(vou->vouctl + VOU_DIV_PARA, DIV_PARA_UPDATE, 0);

	for (i = 0; i < num; i++) {
		struct vou_div_config *cfg = configs + i;
		u32 reg, shift;

		switch (cfg->id) {
		case VOU_DIV_VGA:
			reg = VOU_CLK_SEL;
			shift = bits->div_vga_shift;
			break;
		case VOU_DIV_PIC:
			reg = VOU_CLK_SEL;
			shift = bits->div_pic_shift;
			break;
		case VOU_DIV_TVENC:
			reg = VOU_DIV_PARA;
			shift = bits->div_tvenc_shift;
			break;
		case VOU_DIV_HDMI_PNX:
			reg = VOU_DIV_PARA;
			shift = bits->div_hdmi_pnx_shift;
			break;
		case VOU_DIV_HDMI:
			reg = VOU_DIV_PARA;
			shift = bits->div_hdmi_shift;
			break;
		case VOU_DIV_INF:
			reg = VOU_DIV_PARA;
			shift = bits->div_inf_shift;
			break;
		case VOU_DIV_LAYER:
			reg = VOU_DIV_PARA;
			shift = bits->div_layer_shift;
			break;
		default:
			continue;
		}

		/* Each divider occupies 3 bits */
		zx_writel_mask(vou->vouctl + reg, 0x7 << shift,
			       cfg->val << shift);
	}

	/* Set update flag bit to get dividers effected */
	zx_writel_mask(vou->vouctl + VOU_DIV_PARA, DIV_PARA_UPDATE,
		       DIV_PARA_UPDATE);
}