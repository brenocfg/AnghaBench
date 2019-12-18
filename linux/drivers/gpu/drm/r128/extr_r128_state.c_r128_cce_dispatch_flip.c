#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct drm_device {TYPE_2__* dev_private; } ;
struct TYPE_5__ {scalar_t__ current_page; TYPE_1__* sarea_priv; int /*<<< orphan*/  front_offset; int /*<<< orphan*/  back_offset; } ;
typedef  TYPE_2__ drm_r128_private_t ;
struct TYPE_4__ {scalar_t__ pfCurrentPage; int /*<<< orphan*/  last_frame; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADVANCE_RING () ; 
 int /*<<< orphan*/  BEGIN_RING (int) ; 
 int /*<<< orphan*/  CCE_PACKET0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_DEBUG (char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  OUT_RING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R128_CRTC_OFFSET ; 
 int /*<<< orphan*/  R128_LAST_FRAME_REG ; 
 int /*<<< orphan*/  R128_WAIT_UNTIL_PAGE_FLIPPED () ; 
 int /*<<< orphan*/  RING_LOCALS ; 
 int /*<<< orphan*/  r128_cce_performance_boxes (TYPE_2__*) ; 

__attribute__((used)) static void r128_cce_dispatch_flip(struct drm_device *dev)
{
	drm_r128_private_t *dev_priv = dev->dev_private;
	RING_LOCALS;
	DRM_DEBUG("page=%d pfCurrentPage=%d\n",
		  dev_priv->current_page, dev_priv->sarea_priv->pfCurrentPage);

#if R128_PERFORMANCE_BOXES
	/* Do some trivial performance monitoring...
	 */
	r128_cce_performance_boxes(dev_priv);
#endif

	BEGIN_RING(4);

	R128_WAIT_UNTIL_PAGE_FLIPPED();
	OUT_RING(CCE_PACKET0(R128_CRTC_OFFSET, 0));

	if (dev_priv->current_page == 0)
		OUT_RING(dev_priv->back_offset);
	else
		OUT_RING(dev_priv->front_offset);

	ADVANCE_RING();

	/* Increment the frame counter.  The client-side 3D driver must
	 * throttle the framerate by waiting for this value before
	 * performing the swapbuffer ioctl.
	 */
	dev_priv->sarea_priv->last_frame++;
	dev_priv->sarea_priv->pfCurrentPage = dev_priv->current_page =
	    1 - dev_priv->current_page;

	BEGIN_RING(2);

	OUT_RING(CCE_PACKET0(R128_LAST_FRAME_REG, 0));
	OUT_RING(dev_priv->sarea_priv->last_frame);

	ADVANCE_RING();
}