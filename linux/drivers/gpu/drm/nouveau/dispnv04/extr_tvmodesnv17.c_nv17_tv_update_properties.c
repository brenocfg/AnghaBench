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
struct nv17_tv_state {int ptv_204; int* tv_enc; } ;
struct TYPE_2__ {int /*<<< orphan*/ * tv_enc; } ;
struct nv17_tv_norm_params {TYPE_1__ tv_enc_mode; } ;
struct nv17_tv_encoder {int select_subconnector; int subconnector; int pin_mask; int hue; int /*<<< orphan*/  saturation; struct nv17_tv_state state; } ;
struct drm_encoder {struct drm_device* dev; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
#define  DRM_MODE_SUBCONNECTOR_Component 131 
#define  DRM_MODE_SUBCONNECTOR_Composite 130 
#define  DRM_MODE_SUBCONNECTOR_SCART 129 
#define  DRM_MODE_SUBCONNECTOR_SVIDEO 128 
 struct nv17_tv_norm_params* get_tv_norm (struct drm_encoder*) ; 
 void* interpolate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv_load_ptv (struct drm_device*,struct nv17_tv_state*,int) ; 
 int /*<<< orphan*/  nv_load_tv_enc (struct drm_device*,struct nv17_tv_state*,int) ; 
 struct nv17_tv_encoder* to_tv_enc (struct drm_encoder*) ; 

void nv17_tv_update_properties(struct drm_encoder *encoder)
{
	struct drm_device *dev = encoder->dev;
	struct nv17_tv_encoder *tv_enc = to_tv_enc(encoder);
	struct nv17_tv_state *regs = &tv_enc->state;
	struct nv17_tv_norm_params *tv_norm = get_tv_norm(encoder);
	int subconnector = tv_enc->select_subconnector ?
						tv_enc->select_subconnector :
						tv_enc->subconnector;

	switch (subconnector) {
	case DRM_MODE_SUBCONNECTOR_Composite:
	{
		regs->ptv_204 = 0x2;

		/* The composite connector may be found on either pin. */
		if (tv_enc->pin_mask & 0x4)
			regs->ptv_204 |= 0x010000;
		else if (tv_enc->pin_mask & 0x2)
			regs->ptv_204 |= 0x100000;
		else
			regs->ptv_204 |= 0x110000;

		regs->tv_enc[0x7] = 0x10;
		break;
	}
	case DRM_MODE_SUBCONNECTOR_SVIDEO:
		regs->ptv_204 = 0x11012;
		regs->tv_enc[0x7] = 0x18;
		break;

	case DRM_MODE_SUBCONNECTOR_Component:
		regs->ptv_204 = 0x111333;
		regs->tv_enc[0x7] = 0x14;
		break;

	case DRM_MODE_SUBCONNECTOR_SCART:
		regs->ptv_204 = 0x111012;
		regs->tv_enc[0x7] = 0x18;
		break;
	}

	regs->tv_enc[0x20] = interpolate(0, tv_norm->tv_enc_mode.tv_enc[0x20],
					 255, tv_enc->saturation);
	regs->tv_enc[0x22] = interpolate(0, tv_norm->tv_enc_mode.tv_enc[0x22],
					 255, tv_enc->saturation);
	regs->tv_enc[0x25] = tv_enc->hue * 255 / 100;

	nv_load_ptv(dev, regs, 204);
	nv_load_tv_enc(dev, regs, 7);
	nv_load_tv_enc(dev, regs, 20);
	nv_load_tv_enc(dev, regs, 22);
	nv_load_tv_enc(dev, regs, 25);
}