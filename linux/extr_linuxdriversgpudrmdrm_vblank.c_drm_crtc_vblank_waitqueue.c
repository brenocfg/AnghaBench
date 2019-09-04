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
typedef  int /*<<< orphan*/  wait_queue_head_t ;
struct drm_crtc {TYPE_2__* dev; } ;
struct TYPE_4__ {TYPE_1__* vblank; } ;
struct TYPE_3__ {int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 size_t drm_crtc_index (struct drm_crtc*) ; 

wait_queue_head_t *drm_crtc_vblank_waitqueue(struct drm_crtc *crtc)
{
	return &crtc->dev->vblank[drm_crtc_index(crtc)].queue;
}