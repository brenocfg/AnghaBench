#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  tex_cntl_c; } ;
struct TYPE_13__ {unsigned int dirty; TYPE_1__ context_state; } ;
typedef  TYPE_2__ drm_r128_sarea_t ;
struct TYPE_14__ {TYPE_2__* sarea_priv; } ;
typedef  TYPE_3__ drm_r128_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,unsigned int) ; 
 unsigned int R128_REQUIRE_QUIESCENCE ; 
 int /*<<< orphan*/  R128_TEX_CACHE_FLUSH ; 
 unsigned int R128_UPLOAD_CONTEXT ; 
 unsigned int R128_UPLOAD_CORE ; 
 unsigned int R128_UPLOAD_MASKS ; 
 unsigned int R128_UPLOAD_SETUP ; 
 unsigned int R128_UPLOAD_TEX0 ; 
 unsigned int R128_UPLOAD_TEX1 ; 
 unsigned int R128_UPLOAD_WINDOW ; 
 int /*<<< orphan*/  r128_emit_context (TYPE_3__*) ; 
 int /*<<< orphan*/  r128_emit_core (TYPE_3__*) ; 
 int /*<<< orphan*/  r128_emit_masks (TYPE_3__*) ; 
 int /*<<< orphan*/  r128_emit_setup (TYPE_3__*) ; 
 int /*<<< orphan*/  r128_emit_tex0 (TYPE_3__*) ; 
 int /*<<< orphan*/  r128_emit_tex1 (TYPE_3__*) ; 
 int /*<<< orphan*/  r128_emit_window (TYPE_3__*) ; 

__attribute__((used)) static void r128_emit_state(drm_r128_private_t *dev_priv)
{
	drm_r128_sarea_t *sarea_priv = dev_priv->sarea_priv;
	unsigned int dirty = sarea_priv->dirty;

	DRM_DEBUG("dirty=0x%08x\n", dirty);

	if (dirty & R128_UPLOAD_CORE) {
		r128_emit_core(dev_priv);
		sarea_priv->dirty &= ~R128_UPLOAD_CORE;
	}

	if (dirty & R128_UPLOAD_CONTEXT) {
		r128_emit_context(dev_priv);
		sarea_priv->dirty &= ~R128_UPLOAD_CONTEXT;
	}

	if (dirty & R128_UPLOAD_SETUP) {
		r128_emit_setup(dev_priv);
		sarea_priv->dirty &= ~R128_UPLOAD_SETUP;
	}

	if (dirty & R128_UPLOAD_MASKS) {
		r128_emit_masks(dev_priv);
		sarea_priv->dirty &= ~R128_UPLOAD_MASKS;
	}

	if (dirty & R128_UPLOAD_WINDOW) {
		r128_emit_window(dev_priv);
		sarea_priv->dirty &= ~R128_UPLOAD_WINDOW;
	}

	if (dirty & R128_UPLOAD_TEX0) {
		r128_emit_tex0(dev_priv);
		sarea_priv->dirty &= ~R128_UPLOAD_TEX0;
	}

	if (dirty & R128_UPLOAD_TEX1) {
		r128_emit_tex1(dev_priv);
		sarea_priv->dirty &= ~R128_UPLOAD_TEX1;
	}

	/* Turn off the texture cache flushing */
	sarea_priv->context_state.tex_cntl_c &= ~R128_TEX_CACHE_FLUSH;

	sarea_priv->dirty &= ~R128_REQUIRE_QUIESCENCE;
}