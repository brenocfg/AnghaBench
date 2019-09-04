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
struct dw_hdmi {int /*<<< orphan*/  mutex; int /*<<< orphan*/  mc_clkdis; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDMI_MC_CLKDIS ; 
 int /*<<< orphan*/  HDMI_MC_CLKDIS_CECCLK_DISABLE ; 
 int /*<<< orphan*/  hdmi_writeb (struct dw_hdmi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dw_hdmi_cec_disable(struct dw_hdmi *hdmi)
{
	mutex_lock(&hdmi->mutex);
	hdmi->mc_clkdis |= HDMI_MC_CLKDIS_CECCLK_DISABLE;
	hdmi_writeb(hdmi, hdmi->mc_clkdis, HDMI_MC_CLKDIS);
	mutex_unlock(&hdmi->mutex);
}