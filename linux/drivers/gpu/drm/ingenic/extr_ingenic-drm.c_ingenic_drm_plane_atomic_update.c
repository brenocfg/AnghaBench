#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct ingenic_drm {TYPE_5__* dma_hwdesc; } ;
struct drm_plane_state {TYPE_6__* fb; TYPE_3__* crtc; } ;
struct drm_plane {size_t index; struct drm_plane_state* state; } ;
struct TYPE_12__ {TYPE_4__* format; } ;
struct TYPE_11__ {unsigned int cmd; int /*<<< orphan*/  addr; } ;
struct TYPE_10__ {unsigned int* cpp; } ;
struct TYPE_9__ {TYPE_2__* state; } ;
struct TYPE_7__ {unsigned int hdisplay; unsigned int vdisplay; } ;
struct TYPE_8__ {TYPE_1__ adjusted_mode; } ;

/* Variables and functions */
 unsigned int JZ_LCD_CMD_EOF_IRQ ; 
 int /*<<< orphan*/  drm_fb_cma_get_gem_addr (TYPE_6__*,struct drm_plane_state*,int /*<<< orphan*/ ) ; 
 struct ingenic_drm* drm_plane_get_priv (struct drm_plane*) ; 

__attribute__((used)) static void ingenic_drm_plane_atomic_update(struct drm_plane *plane,
					    struct drm_plane_state *oldstate)
{
	struct ingenic_drm *priv = drm_plane_get_priv(plane);
	struct drm_plane_state *state = plane->state;
	unsigned int width, height, cpp;

	width = state->crtc->state->adjusted_mode.hdisplay;
	height = state->crtc->state->adjusted_mode.vdisplay;
	cpp = state->fb->format->cpp[plane->index];

	priv->dma_hwdesc->addr = drm_fb_cma_get_gem_addr(state->fb, state, 0);
	priv->dma_hwdesc->cmd = width * height * cpp / 4;
	priv->dma_hwdesc->cmd |= JZ_LCD_CMD_EOF_IRQ;
}