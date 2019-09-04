#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct pl111_drm_dev_private {scalar_t__ ienb; scalar_t__ regs; } ;
struct drm_crtc {struct drm_device* dev; } ;
struct drm_simple_display_pipe {struct drm_crtc crtc; } ;
struct drm_device {struct pl111_drm_dev_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void pl111_display_disable_vblank(struct drm_simple_display_pipe *pipe)
{
	struct drm_crtc *crtc = &pipe->crtc;
	struct drm_device *drm = crtc->dev;
	struct pl111_drm_dev_private *priv = drm->dev_private;

	writel(0, priv->regs + priv->ienb);
}