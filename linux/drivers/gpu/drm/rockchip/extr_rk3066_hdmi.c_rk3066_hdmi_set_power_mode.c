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
typedef  int u8 ;
struct rk3066_hdmi {int /*<<< orphan*/  tmdsclk; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_PLLA_RATE ; 
 int /*<<< orphan*/  DRM_DEV_DEBUG (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  HDMI_SYS_CTRL ; 
 int HDMI_SYS_PLLB_RESET ; 
 int HDMI_SYS_PLL_RESET_MASK ; 
 int HDMI_SYS_POWER_MODE_A ; 
 int HDMI_SYS_POWER_MODE_D ; 
 int /*<<< orphan*/  HDMI_SYS_POWER_MODE_MASK ; 
 int /*<<< orphan*/  hdmi_modb (struct rk3066_hdmi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hdmi_writeb (struct rk3066_hdmi*,int /*<<< orphan*/ ,int) ; 
 int rk3066_hdmi_get_power_mode (struct rk3066_hdmi*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void rk3066_hdmi_set_power_mode(struct rk3066_hdmi *hdmi, int mode)
{
	u8 current_mode, next_mode;
	u8 i = 0;

	current_mode = rk3066_hdmi_get_power_mode(hdmi);

	DRM_DEV_DEBUG(hdmi->dev, "mode         :%d\n", mode);
	DRM_DEV_DEBUG(hdmi->dev, "current_mode :%d\n", current_mode);

	if (current_mode == mode)
		return;

	do {
		if (current_mode > mode) {
			next_mode = current_mode / 2;
		} else {
			if (current_mode < HDMI_SYS_POWER_MODE_A)
				next_mode = HDMI_SYS_POWER_MODE_A;
			else
				next_mode = current_mode * 2;
		}

		DRM_DEV_DEBUG(hdmi->dev, "%d: next_mode :%d\n", i, next_mode);

		if (next_mode != HDMI_SYS_POWER_MODE_D) {
			hdmi_modb(hdmi, HDMI_SYS_CTRL,
				  HDMI_SYS_POWER_MODE_MASK, next_mode);
		} else {
			hdmi_writeb(hdmi, HDMI_SYS_CTRL,
				    HDMI_SYS_POWER_MODE_D |
				    HDMI_SYS_PLL_RESET_MASK);
			usleep_range(90, 100);
			hdmi_writeb(hdmi, HDMI_SYS_CTRL,
				    HDMI_SYS_POWER_MODE_D |
				    HDMI_SYS_PLLB_RESET);
			usleep_range(90, 100);
			hdmi_writeb(hdmi, HDMI_SYS_CTRL,
				    HDMI_SYS_POWER_MODE_D);
		}
		current_mode = next_mode;
		i = i + 1;
	} while ((next_mode != mode) && (i < 5));

	/*
	 * When the IP controller isn't configured with accurate video timing,
	 * DDC_CLK should be equal to the PLLA frequency, which is 30MHz,
	 * so we need to init the TMDS rate to the PCLK rate and reconfigure
	 * the DDC clock.
	 */
	if (mode < HDMI_SYS_POWER_MODE_D)
		hdmi->tmdsclk = DEFAULT_PLLA_RATE;
}