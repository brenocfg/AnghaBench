#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct nv04_mode_state {int dummy; } ;
struct TYPE_4__ {int chipset; } ;
struct TYPE_5__ {TYPE_1__ info; } ;
struct TYPE_6__ {TYPE_2__ device; } ;
struct nouveau_drm {TYPE_3__ client; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 
 int /*<<< orphan*/  nouveau_hw_fix_bad_vpll (struct drm_device*,int) ; 
 int /*<<< orphan*/  nv_save_state_ext (struct drm_device*,int,struct nv04_mode_state*) ; 
 int /*<<< orphan*/  nv_save_state_palette (struct drm_device*,int,struct nv04_mode_state*) ; 
 int /*<<< orphan*/  nv_save_state_ramdac (struct drm_device*,int,struct nv04_mode_state*) ; 
 int /*<<< orphan*/  nv_save_state_vga (struct drm_device*,int,struct nv04_mode_state*) ; 

void nouveau_hw_save_state(struct drm_device *dev, int head,
			   struct nv04_mode_state *state)
{
	struct nouveau_drm *drm = nouveau_drm(dev);

	if (drm->client.device.info.chipset == 0x11)
		/* NB: no attempt is made to restore the bad pll later on */
		nouveau_hw_fix_bad_vpll(dev, head);
	nv_save_state_ramdac(dev, head, state);
	nv_save_state_vga(dev, head, state);
	nv_save_state_palette(dev, head, state);
	nv_save_state_ext(dev, head, state);
}