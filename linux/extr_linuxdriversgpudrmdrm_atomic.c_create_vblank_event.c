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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_6__ {int /*<<< orphan*/  user_data; int /*<<< orphan*/  crtc_id; } ;
struct TYPE_7__ {int length; int /*<<< orphan*/  type; } ;
struct TYPE_8__ {TYPE_2__ vbl; TYPE_3__ base; } ;
struct drm_pending_vblank_event {TYPE_4__ event; } ;
struct TYPE_5__ {int /*<<< orphan*/  id; } ;
struct drm_crtc {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_EVENT_FLIP_COMPLETE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct drm_pending_vblank_event* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct drm_pending_vblank_event *create_vblank_event(
		struct drm_crtc *crtc, uint64_t user_data)
{
	struct drm_pending_vblank_event *e = NULL;

	e = kzalloc(sizeof *e, GFP_KERNEL);
	if (!e)
		return NULL;

	e->event.base.type = DRM_EVENT_FLIP_COMPLETE;
	e->event.base.length = sizeof(e->event);
	e->event.vbl.crtc_id = crtc->base.id;
	e->event.vbl.user_data = user_data;

	return e;
}