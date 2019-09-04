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
struct nct7904_data {int bank_sel; int fanin_mask; int vsen_mask; int tcpu_mask; int* fan_mode; int /*<<< orphan*/  bank_lock; struct i2c_client* client; } ;
struct i2c_device_id {int dummy; } ;
struct device {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  name; struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BANK_0 ; 
 int /*<<< orphan*/  BANK_3 ; 
 int /*<<< orphan*/  DTS_T_CTRL0_REG ; 
 int ENOMEM ; 
 scalar_t__ FANCTL1_FMR_REG ; 
 int FANCTL_MAX ; 
 int /*<<< orphan*/  FANIN_CTRL0_REG ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PTR_ERR_OR_ZERO (struct device*) ; 
 int /*<<< orphan*/  VT_ADC_CTRL0_REG ; 
 scalar_t__ VT_ADC_CTRL2_REG ; 
 struct device* devm_hwmon_device_register_with_info (struct device*,int /*<<< orphan*/ ,struct nct7904_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct nct7904_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nct7904_chip_info ; 
 int nct7904_read_reg (struct nct7904_data*,int /*<<< orphan*/ ,scalar_t__) ; 
 int nct7904_read_reg16 (struct nct7904_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nct7904_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	struct nct7904_data *data;
	struct device *hwmon_dev;
	struct device *dev = &client->dev;
	int ret, i;
	u32 mask;

	data = devm_kzalloc(dev, sizeof(struct nct7904_data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	data->client = client;
	mutex_init(&data->bank_lock);
	data->bank_sel = -1;

	/* Setup sensor groups. */
	/* FANIN attributes */
	ret = nct7904_read_reg16(data, BANK_0, FANIN_CTRL0_REG);
	if (ret < 0)
		return ret;
	data->fanin_mask = (ret >> 8) | ((ret & 0xff) << 8);

	/*
	 * VSEN attributes
	 *
	 * Note: voltage sensors overlap with external temperature
	 * sensors. So, if we ever decide to support the latter
	 * we will have to adjust 'vsen_mask' accordingly.
	 */
	mask = 0;
	ret = nct7904_read_reg16(data, BANK_0, VT_ADC_CTRL0_REG);
	if (ret >= 0)
		mask = (ret >> 8) | ((ret & 0xff) << 8);
	ret = nct7904_read_reg(data, BANK_0, VT_ADC_CTRL2_REG);
	if (ret >= 0)
		mask |= (ret << 16);
	data->vsen_mask = mask;

	/* CPU_TEMP attributes */
	ret = nct7904_read_reg16(data, BANK_0, DTS_T_CTRL0_REG);
	if (ret < 0)
		return ret;
	data->tcpu_mask = ((ret >> 8) & 0xf) | ((ret & 0xf) << 4);

	for (i = 0; i < FANCTL_MAX; i++) {
		ret = nct7904_read_reg(data, BANK_3, FANCTL1_FMR_REG + i);
		if (ret < 0)
			return ret;
		data->fan_mode[i] = ret;
	}

	hwmon_dev =
		devm_hwmon_device_register_with_info(dev, client->name, data,
						     &nct7904_chip_info, NULL);
	return PTR_ERR_OR_ZERO(hwmon_dev);
}