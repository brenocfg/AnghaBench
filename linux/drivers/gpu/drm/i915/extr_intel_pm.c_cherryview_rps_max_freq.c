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
struct drm_i915_private {int dummy; } ;
struct TYPE_3__ {int eu_total; } ;
struct TYPE_4__ {TYPE_1__ sseu; } ;

/* Variables and functions */
 int FB_GFX_FMAX_AT_VMAX_2SS4EU_FUSE_SHIFT ; 
 int FB_GFX_FMAX_AT_VMAX_2SS6EU_FUSE_SHIFT ; 
 int FB_GFX_FMAX_AT_VMAX_2SS8EU_FUSE_SHIFT ; 
 int /*<<< orphan*/  FB_GFX_FMAX_AT_VMAX_FUSE ; 
 int FB_GFX_FREQ_FUSE_MASK ; 
 TYPE_2__* RUNTIME_INFO (struct drm_i915_private*) ; 
 int vlv_punit_read (struct drm_i915_private*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cherryview_rps_max_freq(struct drm_i915_private *dev_priv)
{
	u32 val, rp0;

	val = vlv_punit_read(dev_priv, FB_GFX_FMAX_AT_VMAX_FUSE);

	switch (RUNTIME_INFO(dev_priv)->sseu.eu_total) {
	case 8:
		/* (2 * 4) config */
		rp0 = (val >> FB_GFX_FMAX_AT_VMAX_2SS4EU_FUSE_SHIFT);
		break;
	case 12:
		/* (2 * 6) config */
		rp0 = (val >> FB_GFX_FMAX_AT_VMAX_2SS6EU_FUSE_SHIFT);
		break;
	case 16:
		/* (2 * 8) config */
	default:
		/* Setting (2 * 8) Min RP0 for any other combination */
		rp0 = (val >> FB_GFX_FMAX_AT_VMAX_2SS8EU_FUSE_SHIFT);
		break;
	}

	rp0 = (rp0 & FB_GFX_FREQ_FUSE_MASK);

	return rp0;
}