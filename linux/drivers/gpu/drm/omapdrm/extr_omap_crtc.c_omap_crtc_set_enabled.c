#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct omap_irq_wait {int dummy; } ;
struct omap_drm_private {int /*<<< orphan*/  dispc; TYPE_3__* dispc_ops; } ;
struct omap_crtc_state {scalar_t__ manually_updated; } ;
struct omap_crtc {int channel; int enabled; int ignore_digit_sync_lost; int /*<<< orphan*/  name; TYPE_2__* pipe; } ;
struct drm_device {int /*<<< orphan*/  dev; struct omap_drm_private* dev_private; } ;
struct drm_crtc {struct drm_device* dev; int /*<<< orphan*/  state; } ;
typedef  enum omap_channel { ____Placeholder_omap_channel } omap_channel ;
struct TYPE_6__ {int /*<<< orphan*/  (* mgr_enable ) (int /*<<< orphan*/ ,int,int) ;scalar_t__ (* mgr_get_vsync_irq ) (int /*<<< orphan*/ ,int) ;scalar_t__ (* mgr_get_framedone_irq ) (int /*<<< orphan*/ ,int) ;} ;
struct TYPE_5__ {TYPE_1__* output; } ;
struct TYPE_4__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ OMAP_DISPLAY_TYPE_HDMI ; 
 scalar_t__ OMAP_DSS_CHANNEL_DIGIT ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  omap_irq_enable_framedone (struct drm_crtc*,int) ; 
 int omap_irq_wait (struct drm_device*,struct omap_irq_wait*,int /*<<< orphan*/ ) ; 
 struct omap_irq_wait* omap_irq_wait_init (struct drm_device*,scalar_t__,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub3 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,int,int) ; 
 struct omap_crtc* to_omap_crtc (struct drm_crtc*) ; 
 struct omap_crtc_state* to_omap_crtc_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void omap_crtc_set_enabled(struct drm_crtc *crtc, bool enable)
{
	struct omap_crtc_state *omap_state = to_omap_crtc_state(crtc->state);
	struct drm_device *dev = crtc->dev;
	struct omap_drm_private *priv = dev->dev_private;
	struct omap_crtc *omap_crtc = to_omap_crtc(crtc);
	enum omap_channel channel = omap_crtc->channel;
	struct omap_irq_wait *wait;
	u32 framedone_irq, vsync_irq;
	int ret;

	if (WARN_ON(omap_crtc->enabled == enable))
		return;

	if (omap_state->manually_updated) {
		omap_irq_enable_framedone(crtc, enable);
		omap_crtc->enabled = enable;
		return;
	}

	if (omap_crtc->pipe->output->type == OMAP_DISPLAY_TYPE_HDMI) {
		priv->dispc_ops->mgr_enable(priv->dispc, channel, enable);
		omap_crtc->enabled = enable;
		return;
	}

	if (omap_crtc->channel == OMAP_DSS_CHANNEL_DIGIT) {
		/*
		 * Digit output produces some sync lost interrupts during the
		 * first frame when enabling, so we need to ignore those.
		 */
		omap_crtc->ignore_digit_sync_lost = true;
	}

	framedone_irq = priv->dispc_ops->mgr_get_framedone_irq(priv->dispc,
							       channel);
	vsync_irq = priv->dispc_ops->mgr_get_vsync_irq(priv->dispc, channel);

	if (enable) {
		wait = omap_irq_wait_init(dev, vsync_irq, 1);
	} else {
		/*
		 * When we disable the digit output, we need to wait for
		 * FRAMEDONE to know that DISPC has finished with the output.
		 *
		 * OMAP2/3 does not have FRAMEDONE irq for digit output, and in
		 * that case we need to use vsync interrupt, and wait for both
		 * even and odd frames.
		 */

		if (framedone_irq)
			wait = omap_irq_wait_init(dev, framedone_irq, 1);
		else
			wait = omap_irq_wait_init(dev, vsync_irq, 2);
	}

	priv->dispc_ops->mgr_enable(priv->dispc, channel, enable);
	omap_crtc->enabled = enable;

	ret = omap_irq_wait(dev, wait, msecs_to_jiffies(100));
	if (ret) {
		dev_err(dev->dev, "%s: timeout waiting for %s\n",
				omap_crtc->name, enable ? "enable" : "disable");
	}

	if (omap_crtc->channel == OMAP_DSS_CHANNEL_DIGIT) {
		omap_crtc->ignore_digit_sync_lost = false;
		/* make sure the irq handler sees the value above */
		mb();
	}
}