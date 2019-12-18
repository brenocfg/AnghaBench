#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned int texorg; } ;
typedef  TYPE_1__ drm_mga_texture_regs_t ;
struct TYPE_6__ {TYPE_1__* tex_state; } ;
typedef  TYPE_2__ drm_mga_sarea_t ;
struct TYPE_7__ {TYPE_2__* sarea_priv; } ;
typedef  TYPE_3__ drm_mga_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,unsigned int,int) ; 
 int EINVAL ; 
 unsigned int MGA_TEXORGACC_MASK ; 
 unsigned int MGA_TEXORGACC_PCI ; 
 unsigned int MGA_TEXORGMAP_MASK ; 
 unsigned int MGA_TEXORGMAP_SYSMEM ; 

__attribute__((used)) static int mga_verify_tex(drm_mga_private_t *dev_priv, int unit)
{
	drm_mga_sarea_t *sarea_priv = dev_priv->sarea_priv;
	drm_mga_texture_regs_t *tex = &sarea_priv->tex_state[unit];
	unsigned int org;

	org = tex->texorg & (MGA_TEXORGMAP_MASK | MGA_TEXORGACC_MASK);

	if (org == (MGA_TEXORGMAP_SYSMEM | MGA_TEXORGACC_PCI)) {
		DRM_ERROR("*** bad TEXORG: 0x%x, unit %d\n", tex->texorg, unit);
		tex->texorg = 0;
		return -EINVAL;
	}

	return 0;
}