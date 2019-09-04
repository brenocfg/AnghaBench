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
struct TYPE_4__ {int x1; int y1; } ;
struct drm_plane_state {TYPE_2__ src; struct drm_framebuffer* fb; } ;
struct drm_gem_cma_object {unsigned long paddr; } ;
struct drm_framebuffer {unsigned long* offsets; int* pitches; TYPE_1__* format; } ;
struct TYPE_3__ {int* cpp; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct drm_gem_cma_object* drm_fb_cma_get_gem_obj (struct drm_framebuffer*,int) ; 

__attribute__((used)) static inline unsigned long
drm_plane_state_to_eba(struct drm_plane_state *state, int plane)
{
	struct drm_framebuffer *fb = state->fb;
	struct drm_gem_cma_object *cma_obj;
	int x = state->src.x1 >> 16;
	int y = state->src.y1 >> 16;

	cma_obj = drm_fb_cma_get_gem_obj(fb, plane);
	BUG_ON(!cma_obj);

	return cma_obj->paddr + fb->offsets[plane] + fb->pitches[plane] * y +
	       fb->format->cpp[plane] * x;
}