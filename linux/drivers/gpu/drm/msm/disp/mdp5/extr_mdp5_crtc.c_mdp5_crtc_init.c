#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  irq; } ;
struct TYPE_7__ {int /*<<< orphan*/  irq; } ;
struct TYPE_6__ {int /*<<< orphan*/  irq; } ;
struct TYPE_5__ {int /*<<< orphan*/  lock; } ;
struct drm_crtc {int dummy; } ;
struct mdp5_crtc {int id; int lm_cursor_enabled; int /*<<< orphan*/  unref_cursor_work; TYPE_4__ pp_done; TYPE_3__ err; TYPE_2__ vblank; int /*<<< orphan*/  pp_completion; TYPE_1__ cursor; int /*<<< orphan*/  lm_lock; struct drm_crtc base; } ;
struct drm_plane {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct drm_crtc* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  drm_crtc_helper_add (struct drm_crtc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_crtc_init_with_planes (struct drm_device*,struct drm_crtc*,struct drm_plane*,struct drm_plane*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_flip_work_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 struct mdp5_crtc* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdp5_crtc_err_irq ; 
 int /*<<< orphan*/  mdp5_crtc_funcs ; 
 int /*<<< orphan*/  mdp5_crtc_helper_funcs ; 
 int /*<<< orphan*/  mdp5_crtc_pp_done_irq ; 
 int /*<<< orphan*/  mdp5_crtc_vblank_irq ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unref_cursor_worker ; 

struct drm_crtc *mdp5_crtc_init(struct drm_device *dev,
				struct drm_plane *plane,
				struct drm_plane *cursor_plane, int id)
{
	struct drm_crtc *crtc = NULL;
	struct mdp5_crtc *mdp5_crtc;

	mdp5_crtc = kzalloc(sizeof(*mdp5_crtc), GFP_KERNEL);
	if (!mdp5_crtc)
		return ERR_PTR(-ENOMEM);

	crtc = &mdp5_crtc->base;

	mdp5_crtc->id = id;

	spin_lock_init(&mdp5_crtc->lm_lock);
	spin_lock_init(&mdp5_crtc->cursor.lock);
	init_completion(&mdp5_crtc->pp_completion);

	mdp5_crtc->vblank.irq = mdp5_crtc_vblank_irq;
	mdp5_crtc->err.irq = mdp5_crtc_err_irq;
	mdp5_crtc->pp_done.irq = mdp5_crtc_pp_done_irq;

	mdp5_crtc->lm_cursor_enabled = cursor_plane ? false : true;

	drm_crtc_init_with_planes(dev, crtc, plane, cursor_plane,
				  &mdp5_crtc_funcs, NULL);

	drm_flip_work_init(&mdp5_crtc->unref_cursor_work,
			"unref cursor", unref_cursor_worker);

	drm_crtc_helper_add(crtc, &mdp5_crtc_helper_funcs);

	return crtc;
}