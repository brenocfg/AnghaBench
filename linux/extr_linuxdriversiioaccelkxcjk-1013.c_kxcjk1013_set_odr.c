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
struct kxcjk1013_data {scalar_t__ chipset; TYPE_1__* client; int /*<<< orphan*/  odr_bits; } ;
struct kx_odr_map {int /*<<< orphan*/  wuf_bits; int /*<<< orphan*/  odr_bits; } ;
typedef  enum kxcjk1013_mode { ____Placeholder_kxcjk1013_mode } kxcjk1013_mode ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct kx_odr_map const*) ; 
 int /*<<< orphan*/  KXCJK1013_REG_CTRL2 ; 
 int /*<<< orphan*/  KXCJK1013_REG_DATA_CTRL ; 
 scalar_t__ KXTF9 ; 
 int OPERATION ; 
 int PTR_ERR (struct kx_odr_map const*) ; 
 int STANDBY ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int i2c_smbus_write_byte_data (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct kx_odr_map* kxcjk1013_find_odr_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int kxcjk1013_get_mode (struct kxcjk1013_data*,int*) ; 
 int kxcjk1013_set_mode (struct kxcjk1013_data*,int) ; 
 int /*<<< orphan*/  kxtf9_samp_freq_table ; 
 int /*<<< orphan*/  samp_freq_table ; 

__attribute__((used)) static int kxcjk1013_set_odr(struct kxcjk1013_data *data, int val, int val2)
{
	int ret;
	enum kxcjk1013_mode store_mode;
	const struct kx_odr_map *odr_setting;

	ret = kxcjk1013_get_mode(data, &store_mode);
	if (ret < 0)
		return ret;

	if (data->chipset == KXTF9)
		odr_setting = kxcjk1013_find_odr_value(kxtf9_samp_freq_table,
						       ARRAY_SIZE(kxtf9_samp_freq_table),
						       val, val2);
	else
		odr_setting = kxcjk1013_find_odr_value(samp_freq_table,
						       ARRAY_SIZE(samp_freq_table),
						       val, val2);

	if (IS_ERR(odr_setting))
		return PTR_ERR(odr_setting);

	/* To change ODR, the chip must be set to STANDBY as per spec */
	ret = kxcjk1013_set_mode(data, STANDBY);
	if (ret < 0)
		return ret;

	ret = i2c_smbus_write_byte_data(data->client, KXCJK1013_REG_DATA_CTRL,
					odr_setting->odr_bits);
	if (ret < 0) {
		dev_err(&data->client->dev, "Error writing data_ctrl\n");
		return ret;
	}

	data->odr_bits = odr_setting->odr_bits;

	ret = i2c_smbus_write_byte_data(data->client, KXCJK1013_REG_CTRL2,
					odr_setting->wuf_bits);
	if (ret < 0) {
		dev_err(&data->client->dev, "Error writing reg_ctrl2\n");
		return ret;
	}

	if (store_mode == OPERATION) {
		ret = kxcjk1013_set_mode(data, OPERATION);
		if (ret < 0)
			return ret;
	}

	return 0;
}