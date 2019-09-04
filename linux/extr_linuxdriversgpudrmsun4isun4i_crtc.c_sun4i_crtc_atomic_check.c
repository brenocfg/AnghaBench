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
struct sunxi_engine {TYPE_1__* ops; } ;
struct sun4i_crtc {struct sunxi_engine* engine; } ;
struct drm_crtc_state {int dummy; } ;
struct drm_crtc {int dummy; } ;
struct TYPE_2__ {int (* atomic_check ) (struct sunxi_engine*,struct drm_crtc_state*) ;} ;

/* Variables and functions */
 struct sun4i_crtc* drm_crtc_to_sun4i_crtc (struct drm_crtc*) ; 
 int stub1 (struct sunxi_engine*,struct drm_crtc_state*) ; 

__attribute__((used)) static int sun4i_crtc_atomic_check(struct drm_crtc *crtc,
				    struct drm_crtc_state *state)
{
	struct sun4i_crtc *scrtc = drm_crtc_to_sun4i_crtc(crtc);
	struct sunxi_engine *engine = scrtc->engine;
	int ret = 0;

	if (engine && engine->ops && engine->ops->atomic_check)
		ret = engine->ops->atomic_check(engine, state);

	return ret;
}