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
struct drm_crtc {TYPE_3__* dev; } ;
struct armada_private {int /*<<< orphan*/ ** dcrtc; } ;
struct TYPE_8__ {int /*<<< orphan*/  port; } ;
struct armada_crtc {size_t num; TYPE_4__ crtc; scalar_t__ base; TYPE_2__* variant; TYPE_1__* cursor_obj; } ;
struct TYPE_7__ {struct armada_private* dev_private; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* disable ) (struct armada_crtc*) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  obj; } ;

/* Variables and functions */
 scalar_t__ LCD_SPU_IRQ_ENA ; 
 int /*<<< orphan*/  drm_crtc_cleanup (TYPE_4__*) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (int /*<<< orphan*/ *) ; 
 struct armada_crtc* drm_to_armada_crtc (struct drm_crtc*) ; 
 int /*<<< orphan*/  kfree (struct armada_crtc*) ; 
 int /*<<< orphan*/  of_node_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct armada_crtc*) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void armada_drm_crtc_destroy(struct drm_crtc *crtc)
{
	struct armada_crtc *dcrtc = drm_to_armada_crtc(crtc);
	struct armada_private *priv = crtc->dev->dev_private;

	if (dcrtc->cursor_obj)
		drm_gem_object_put_unlocked(&dcrtc->cursor_obj->obj);

	priv->dcrtc[dcrtc->num] = NULL;
	drm_crtc_cleanup(&dcrtc->crtc);

	if (dcrtc->variant->disable)
		dcrtc->variant->disable(dcrtc);

	writel_relaxed(0, dcrtc->base + LCD_SPU_IRQ_ENA);

	of_node_put(dcrtc->crtc.port);

	kfree(dcrtc);
}