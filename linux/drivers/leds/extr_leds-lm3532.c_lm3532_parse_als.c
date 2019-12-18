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
struct lm3532_data {struct lm3532_als_data* als_data; TYPE_1__* client; int /*<<< orphan*/  dev; } ;
struct lm3532_als_data {int als_vmin; int als_vmax; scalar_t__ als_input_mode; scalar_t__ als_avrg_time; void* als2_imp_sel; void* als1_imp_sel; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ LM3532_ALS_WINDOW_mV ; 
 scalar_t__ LM3532_BL_MODE_ALS ; 
 int device_property_read_u32 (int /*<<< orphan*/ *,char*,int*) ; 
 int device_property_read_u8 (int /*<<< orphan*/ *,char*,scalar_t__*) ; 
 struct lm3532_als_data* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ lm3532_get_als_avg_index (int) ; 
 void* lm3532_get_als_imp_index (int) ; 

__attribute__((used)) static int lm3532_parse_als(struct lm3532_data *priv)
{
	struct lm3532_als_data *als;
	int als_avg_time;
	int als_impedance;
	int ret;

	als = devm_kzalloc(priv->dev, sizeof(*als), GFP_KERNEL);
	if (als == NULL)
		return -ENOMEM;

	ret = device_property_read_u32(&priv->client->dev, "ti,als-vmin",
				       &als->als_vmin);
	if (ret)
		als->als_vmin = 0;

	ret = device_property_read_u32(&priv->client->dev, "ti,als-vmax",
				       &als->als_vmax);
	if (ret)
		als->als_vmax = LM3532_ALS_WINDOW_mV;

	if (als->als_vmax > LM3532_ALS_WINDOW_mV) {
		ret = -EINVAL;
		return ret;
	}

	ret = device_property_read_u32(&priv->client->dev, "ti,als1-imp-sel",
				      &als_impedance);
	if (ret)
		als->als1_imp_sel = 0;
	else
		als->als1_imp_sel = lm3532_get_als_imp_index(als_impedance);

	ret = device_property_read_u32(&priv->client->dev, "ti,als2-imp-sel",
				      &als_impedance);
	if (ret)
		als->als2_imp_sel = 0;
	else
		als->als2_imp_sel = lm3532_get_als_imp_index(als_impedance);

	ret = device_property_read_u32(&priv->client->dev, "ti,als-avrg-time-us",
				      &als_avg_time);
	if (ret)
		als->als_avrg_time = 0;
	else
		als->als_avrg_time = lm3532_get_als_avg_index(als_avg_time);

	ret = device_property_read_u8(&priv->client->dev, "ti,als-input-mode",
				      &als->als_input_mode);
	if (ret)
		als->als_input_mode = 0;

	if (als->als_input_mode > LM3532_BL_MODE_ALS) {
		ret = -EINVAL;
		return ret;
	}

	priv->als_data = als;

	return ret;
}