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
typedef  int u32 ;
struct tegra_dc {int /*<<< orphan*/  dev; int /*<<< orphan*/  stats; scalar_t__ rgb; } ;
struct drm_crtc_state {int dummy; } ;
struct drm_crtc {TYPE_2__* dev; TYPE_1__* state; } ;
struct TYPE_4__ {int /*<<< orphan*/  event_lock; } ;
struct TYPE_3__ {int /*<<< orphan*/ * event; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_CMD_DISPLAY_POWER_CONTROL ; 
 int PM0_ENABLE ; 
 int PM1_ENABLE ; 
 int PW0_ENABLE ; 
 int PW1_ENABLE ; 
 int PW2_ENABLE ; 
 int PW3_ENABLE ; 
 int PW4_ENABLE ; 
 int /*<<< orphan*/  drm_crtc_send_vblank_event (struct drm_crtc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_crtc_vblank_off (struct drm_crtc*) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tegra_dc_idle (struct tegra_dc*) ; 
 int tegra_dc_readl (struct tegra_dc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_dc_stats_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tegra_dc_stop (struct tegra_dc*) ; 
 int /*<<< orphan*/  tegra_dc_wait_idle (struct tegra_dc*,int) ; 
 int /*<<< orphan*/  tegra_dc_writel (struct tegra_dc*,int,int /*<<< orphan*/ ) ; 
 struct tegra_dc* to_tegra_dc (struct drm_crtc*) ; 

__attribute__((used)) static void tegra_crtc_atomic_disable(struct drm_crtc *crtc,
				      struct drm_crtc_state *old_state)
{
	struct tegra_dc *dc = to_tegra_dc(crtc);
	u32 value;

	if (!tegra_dc_idle(dc)) {
		tegra_dc_stop(dc);

		/*
		 * Ignore the return value, there isn't anything useful to do
		 * in case this fails.
		 */
		tegra_dc_wait_idle(dc, 100);
	}

	/*
	 * This should really be part of the RGB encoder driver, but clearing
	 * these bits has the side-effect of stopping the display controller.
	 * When that happens no VBLANK interrupts will be raised. At the same
	 * time the encoder is disabled before the display controller, so the
	 * above code is always going to timeout waiting for the controller
	 * to go idle.
	 *
	 * Given the close coupling between the RGB encoder and the display
	 * controller doing it here is still kind of okay. None of the other
	 * encoder drivers require these bits to be cleared.
	 *
	 * XXX: Perhaps given that the display controller is switched off at
	 * this point anyway maybe clearing these bits isn't even useful for
	 * the RGB encoder?
	 */
	if (dc->rgb) {
		value = tegra_dc_readl(dc, DC_CMD_DISPLAY_POWER_CONTROL);
		value &= ~(PW0_ENABLE | PW1_ENABLE | PW2_ENABLE | PW3_ENABLE |
			   PW4_ENABLE | PM0_ENABLE | PM1_ENABLE);
		tegra_dc_writel(dc, value, DC_CMD_DISPLAY_POWER_CONTROL);
	}

	tegra_dc_stats_reset(&dc->stats);
	drm_crtc_vblank_off(crtc);

	spin_lock_irq(&crtc->dev->event_lock);

	if (crtc->state->event) {
		drm_crtc_send_vblank_event(crtc, crtc->state->event);
		crtc->state->event = NULL;
	}

	spin_unlock_irq(&crtc->dev->event_lock);

	pm_runtime_put_sync(dc->dev);
}