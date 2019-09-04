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
typedef  int u32 ;
struct drm_psb_private {int dummy; } ;
struct drm_device {scalar_t__ dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  HISTOGRAM_INT_CONTROL ; 
 int HISTOGRAM_INT_CTRL_CLEAR ; 
 int /*<<< orphan*/  HISTOGRAM_LOGIC_CONTROL ; 
 int /*<<< orphan*/  PIPE_DPST_EVENT_ENABLE ; 
 int PSB_RVDC32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PSB_WVDC32 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PWM_CONTROL_LOGIC ; 
 int PWM_PHASEIN_ENABLE ; 
 int PWM_PHASEIN_INT_ENABLE ; 
 scalar_t__ gma_power_begin (struct drm_device*,int) ; 
 int /*<<< orphan*/  gma_power_end (struct drm_device*) ; 
 int /*<<< orphan*/  psb_enable_pipestat (struct drm_psb_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void psb_irq_turn_on_dpst(struct drm_device *dev)
{
	struct drm_psb_private *dev_priv =
		(struct drm_psb_private *) dev->dev_private;
	u32 hist_reg;
	u32 pwm_reg;

	if (gma_power_begin(dev, false)) {
		PSB_WVDC32(1 << 31, HISTOGRAM_LOGIC_CONTROL);
		hist_reg = PSB_RVDC32(HISTOGRAM_LOGIC_CONTROL);
		PSB_WVDC32(1 << 31, HISTOGRAM_INT_CONTROL);
		hist_reg = PSB_RVDC32(HISTOGRAM_INT_CONTROL);

		PSB_WVDC32(0x80010100, PWM_CONTROL_LOGIC);
		pwm_reg = PSB_RVDC32(PWM_CONTROL_LOGIC);
		PSB_WVDC32(pwm_reg | PWM_PHASEIN_ENABLE
						| PWM_PHASEIN_INT_ENABLE,
							   PWM_CONTROL_LOGIC);
		pwm_reg = PSB_RVDC32(PWM_CONTROL_LOGIC);

		psb_enable_pipestat(dev_priv, 0, PIPE_DPST_EVENT_ENABLE);

		hist_reg = PSB_RVDC32(HISTOGRAM_INT_CONTROL);
		PSB_WVDC32(hist_reg | HISTOGRAM_INT_CTRL_CLEAR,
							HISTOGRAM_INT_CONTROL);
		pwm_reg = PSB_RVDC32(PWM_CONTROL_LOGIC);
		PSB_WVDC32(pwm_reg | 0x80010100 | PWM_PHASEIN_ENABLE,
							PWM_CONTROL_LOGIC);

		gma_power_end(dev);
	}
}