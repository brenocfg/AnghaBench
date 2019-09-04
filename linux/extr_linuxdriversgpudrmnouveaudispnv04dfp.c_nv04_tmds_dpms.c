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
struct nouveau_encoder {int last_dpms; TYPE_1__* dcb; } ;
struct nouveau_drm {int dummy; } ;
struct drm_encoder {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  NV_DEBUG (struct nouveau_drm*,char*,int,int /*<<< orphan*/ ) ; 
 struct nouveau_drm* nouveau_drm (int /*<<< orphan*/ ) ; 
 struct nouveau_encoder* nouveau_encoder (struct drm_encoder*) ; 
 int /*<<< orphan*/  nv04_dfp_update_backlight (struct drm_encoder*,int) ; 
 int /*<<< orphan*/  nv04_dfp_update_fp_control (struct drm_encoder*,int) ; 

__attribute__((used)) static void nv04_tmds_dpms(struct drm_encoder *encoder, int mode)
{
	struct nouveau_drm *drm = nouveau_drm(encoder->dev);
	struct nouveau_encoder *nv_encoder = nouveau_encoder(encoder);

	if (nv_encoder->last_dpms == mode)
		return;
	nv_encoder->last_dpms = mode;

	NV_DEBUG(drm, "Setting dpms mode %d on tmds encoder (output %d)\n",
		 mode, nv_encoder->dcb->index);

	nv04_dfp_update_backlight(encoder, mode);
	nv04_dfp_update_fp_control(encoder, mode);
}