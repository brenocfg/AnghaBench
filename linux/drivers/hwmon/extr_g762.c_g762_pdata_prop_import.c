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
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct g762_platform_data {int /*<<< orphan*/  clk_freq; int /*<<< orphan*/  fan_startv; int /*<<< orphan*/  pwm_polarity; int /*<<< orphan*/  fan_gear_mode; } ;

/* Variables and functions */
 struct g762_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int do_set_clk_freq (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int do_set_fan_gear_mode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int do_set_fan_startv (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int do_set_pwm_polarity (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int g762_pdata_prop_import(struct i2c_client *client)
{
	struct g762_platform_data *pdata = dev_get_platdata(&client->dev);
	int ret;

	if (!pdata)
		return 0;

	ret = do_set_fan_gear_mode(&client->dev, pdata->fan_gear_mode);
	if (ret)
		return ret;

	ret = do_set_pwm_polarity(&client->dev, pdata->pwm_polarity);
	if (ret)
		return ret;

	ret = do_set_fan_startv(&client->dev, pdata->fan_startv);
	if (ret)
		return ret;

	return do_set_clk_freq(&client->dev, pdata->clk_freq);
}