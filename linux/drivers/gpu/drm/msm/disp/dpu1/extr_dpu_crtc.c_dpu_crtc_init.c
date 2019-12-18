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
struct msm_drm_private {int /*<<< orphan*/  kms; } ;
struct drm_plane {int dummy; } ;
struct drm_device {struct msm_drm_private* dev_private; } ;
struct TYPE_3__ {int id; } ;
struct drm_crtc {TYPE_1__ base; struct drm_device* dev; } ;
struct dpu_kms {int dummy; } ;
struct dpu_crtc {int /*<<< orphan*/  name; int /*<<< orphan*/  event_lock; TYPE_2__* frame_events; int /*<<< orphan*/  frame_event_list; int /*<<< orphan*/  frame_done_comp; int /*<<< orphan*/  frame_pending; int /*<<< orphan*/  spin_lock; struct drm_crtc base; } ;
struct TYPE_4__ {int /*<<< orphan*/  work; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_2__*) ; 
 int /*<<< orphan*/  DPU_CRTC_NAME_SIZE ; 
 int /*<<< orphan*/  DPU_DEBUG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct drm_crtc* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpu_crtc_frame_event_work ; 
 int /*<<< orphan*/  dpu_crtc_funcs ; 
 int /*<<< orphan*/  dpu_crtc_helper_funcs ; 
 int /*<<< orphan*/  drm_crtc_helper_add (struct drm_crtc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_crtc_init_with_planes (struct drm_device*,struct drm_crtc*,struct drm_plane*,struct drm_plane*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kthread_init_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct dpu_crtc* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 struct dpu_kms* to_dpu_kms (int /*<<< orphan*/ ) ; 

struct drm_crtc *dpu_crtc_init(struct drm_device *dev, struct drm_plane *plane,
				struct drm_plane *cursor)
{
	struct drm_crtc *crtc = NULL;
	struct dpu_crtc *dpu_crtc = NULL;
	struct msm_drm_private *priv = NULL;
	struct dpu_kms *kms = NULL;
	int i;

	priv = dev->dev_private;
	kms = to_dpu_kms(priv->kms);

	dpu_crtc = kzalloc(sizeof(*dpu_crtc), GFP_KERNEL);
	if (!dpu_crtc)
		return ERR_PTR(-ENOMEM);

	crtc = &dpu_crtc->base;
	crtc->dev = dev;

	spin_lock_init(&dpu_crtc->spin_lock);
	atomic_set(&dpu_crtc->frame_pending, 0);

	init_completion(&dpu_crtc->frame_done_comp);

	INIT_LIST_HEAD(&dpu_crtc->frame_event_list);

	for (i = 0; i < ARRAY_SIZE(dpu_crtc->frame_events); i++) {
		INIT_LIST_HEAD(&dpu_crtc->frame_events[i].list);
		list_add(&dpu_crtc->frame_events[i].list,
				&dpu_crtc->frame_event_list);
		kthread_init_work(&dpu_crtc->frame_events[i].work,
				dpu_crtc_frame_event_work);
	}

	drm_crtc_init_with_planes(dev, crtc, plane, cursor, &dpu_crtc_funcs,
				NULL);

	drm_crtc_helper_add(crtc, &dpu_crtc_helper_funcs);

	/* save user friendly CRTC name for later */
	snprintf(dpu_crtc->name, DPU_CRTC_NAME_SIZE, "crtc%u", crtc->base.id);

	/* initialize event handling */
	spin_lock_init(&dpu_crtc->event_lock);

	DPU_DEBUG("%s: successfully initialized crtc\n", dpu_crtc->name);
	return crtc;
}