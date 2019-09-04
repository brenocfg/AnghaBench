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
typedef  int /*<<< orphan*/  u32 ;
struct sun4i_hdmi {int /*<<< orphan*/  ddc_clk; int /*<<< orphan*/  field_ddc_sda_en; int /*<<< orphan*/  field_ddc_sck_en; int /*<<< orphan*/  field_ddc_reset; int /*<<< orphan*/  field_ddc_en; } ;
struct i2c_msg {scalar_t__ len; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 scalar_t__ SUN4I_HDMI_DDC_BYTE_COUNT_MAX ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_set_rate (int /*<<< orphan*/ ,int) ; 
 struct sun4i_hdmi* i2c_get_adapdata (struct i2c_adapter*) ; 
 scalar_t__ regmap_field_read_poll_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  regmap_field_write (int /*<<< orphan*/ ,int) ; 
 int xfer_msg (struct sun4i_hdmi*,struct i2c_msg*) ; 

__attribute__((used)) static int sun4i_hdmi_i2c_xfer(struct i2c_adapter *adap,
			       struct i2c_msg *msgs, int num)
{
	struct sun4i_hdmi *hdmi = i2c_get_adapdata(adap);
	u32 reg;
	int err, i, ret = num;

	for (i = 0; i < num; i++) {
		if (!msgs[i].len)
			return -EINVAL;
		if (msgs[i].len > SUN4I_HDMI_DDC_BYTE_COUNT_MAX)
			return -EINVAL;
	}

	/* DDC clock needs to be enabled for the module to work */
	clk_prepare_enable(hdmi->ddc_clk);
	clk_set_rate(hdmi->ddc_clk, 100000);

	/* Reset I2C controller */
	regmap_field_write(hdmi->field_ddc_en, 1);
	regmap_field_write(hdmi->field_ddc_reset, 1);
	if (regmap_field_read_poll_timeout(hdmi->field_ddc_reset,
					   reg, !reg, 100, 2000)) {
		clk_disable_unprepare(hdmi->ddc_clk);
		return -EIO;
	}

	regmap_field_write(hdmi->field_ddc_sck_en, 1);
	regmap_field_write(hdmi->field_ddc_sda_en, 1);

	for (i = 0; i < num; i++) {
		err = xfer_msg(hdmi, &msgs[i]);
		if (err) {
			ret = err;
			break;
		}
	}

	clk_disable_unprepare(hdmi->ddc_clk);
	return ret;
}