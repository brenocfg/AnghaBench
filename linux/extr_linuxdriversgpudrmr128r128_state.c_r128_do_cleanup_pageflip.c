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
struct drm_device {TYPE_1__* dev_private; } ;
struct TYPE_2__ {scalar_t__ current_page; scalar_t__ page_flipping; int /*<<< orphan*/  crtc_offset_cntl; int /*<<< orphan*/  crtc_offset; } ;
typedef  TYPE_1__ drm_r128_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  COMMIT_RING () ; 
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int /*<<< orphan*/  R128_CRTC_OFFSET ; 
 int /*<<< orphan*/  R128_CRTC_OFFSET_CNTL ; 
 int /*<<< orphan*/  R128_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r128_cce_dispatch_flip (struct drm_device*) ; 

__attribute__((used)) static int r128_do_cleanup_pageflip(struct drm_device *dev)
{
	drm_r128_private_t *dev_priv = dev->dev_private;
	DRM_DEBUG("\n");

	R128_WRITE(R128_CRTC_OFFSET, dev_priv->crtc_offset);
	R128_WRITE(R128_CRTC_OFFSET_CNTL, dev_priv->crtc_offset_cntl);

	if (dev_priv->current_page != 0) {
		r128_cce_dispatch_flip(dev);
		COMMIT_RING();
	}

	dev_priv->page_flipping = 0;
	return 0;
}