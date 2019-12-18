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
struct dw_hdmi {int /*<<< orphan*/  ddc; TYPE_1__* i2c; scalar_t__ cec_clk; scalar_t__ isfr_clk; scalar_t__ iahb_clk; scalar_t__ cec; scalar_t__ audio; } ;
struct TYPE_2__ {int /*<<< orphan*/  adap; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDMI_IH_MUTE_PHY_STAT0 ; 
 int /*<<< orphan*/  IS_ERR (scalar_t__) ; 
 int /*<<< orphan*/  clk_disable_unprepare (scalar_t__) ; 
 int /*<<< orphan*/  hdmi_writeb (struct dw_hdmi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_put_adapter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_device_unregister (scalar_t__) ; 

__attribute__((used)) static void __dw_hdmi_remove(struct dw_hdmi *hdmi)
{
	if (hdmi->audio && !IS_ERR(hdmi->audio))
		platform_device_unregister(hdmi->audio);
	if (!IS_ERR(hdmi->cec))
		platform_device_unregister(hdmi->cec);

	/* Disable all interrupts */
	hdmi_writeb(hdmi, ~0, HDMI_IH_MUTE_PHY_STAT0);

	clk_disable_unprepare(hdmi->iahb_clk);
	clk_disable_unprepare(hdmi->isfr_clk);
	if (hdmi->cec_clk)
		clk_disable_unprepare(hdmi->cec_clk);

	if (hdmi->i2c)
		i2c_del_adapter(&hdmi->i2c->adap);
	else
		i2c_put_adapter(hdmi->ddc);
}