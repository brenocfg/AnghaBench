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
struct sun4i_hdmi {int /*<<< orphan*/  bus_clk; int /*<<< orphan*/  mod_clk; int /*<<< orphan*/  ddc_i2c; int /*<<< orphan*/  i2c; int /*<<< orphan*/  encoder; int /*<<< orphan*/  connector; int /*<<< orphan*/  cec_adap; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cec_unregister_adapter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct sun4i_hdmi* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  drm_connector_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_encoder_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_put_adapter (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sun4i_hdmi_unbind(struct device *dev, struct device *master,
			    void *data)
{
	struct sun4i_hdmi *hdmi = dev_get_drvdata(dev);

	cec_unregister_adapter(hdmi->cec_adap);
	drm_connector_cleanup(&hdmi->connector);
	drm_encoder_cleanup(&hdmi->encoder);
	i2c_del_adapter(hdmi->i2c);
	i2c_put_adapter(hdmi->ddc_i2c);
	clk_disable_unprepare(hdmi->mod_clk);
	clk_disable_unprepare(hdmi->bus_clk);
}