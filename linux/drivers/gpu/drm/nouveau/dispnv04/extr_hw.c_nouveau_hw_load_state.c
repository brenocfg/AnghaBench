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
struct nv04_mode_state {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVVgaProtect (struct drm_device*,int,int) ; 
 int /*<<< orphan*/  nouveau_hw_load_state_palette (struct drm_device*,int,struct nv04_mode_state*) ; 
 int /*<<< orphan*/  nv_load_state_ext (struct drm_device*,int,struct nv04_mode_state*) ; 
 int /*<<< orphan*/  nv_load_state_ramdac (struct drm_device*,int,struct nv04_mode_state*) ; 
 int /*<<< orphan*/  nv_load_state_vga (struct drm_device*,int,struct nv04_mode_state*) ; 

void nouveau_hw_load_state(struct drm_device *dev, int head,
			   struct nv04_mode_state *state)
{
	NVVgaProtect(dev, head, true);
	nv_load_state_ramdac(dev, head, state);
	nv_load_state_ext(dev, head, state);
	nouveau_hw_load_state_palette(dev, head, state);
	nv_load_state_vga(dev, head, state);
	NVVgaProtect(dev, head, false);
}