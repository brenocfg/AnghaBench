#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_17__ {struct isl1208_state* priv; int /*<<< orphan*/  size; } ;
struct isl1208_state {TYPE_1__* rtc; TYPE_3__ nvmem_config; TYPE_5__* config; } ;
struct i2c_device_id {size_t driver_data; } ;
struct TYPE_19__ {struct device_node* of_node; } ;
struct i2c_client {int irq; TYPE_6__ dev; int /*<<< orphan*/  adapter; } ;
struct device_node {int dummy; } ;
struct TYPE_18__ {scalar_t__ has_timestamp; scalar_t__ has_tamper; int /*<<< orphan*/  nvmem_length; } ;
struct TYPE_16__ {int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_FUNC_I2C ; 
 int ISL1208_REG_SR_RTCF ; 
 int /*<<< orphan*/  ISL1219_REG_EV ; 
 int ISL1219_REG_EV_EVEN ; 
 int ISL1219_REG_EV_EVIENB ; 
 size_t ISL_LAST_ID ; 
 scalar_t__ IS_ERR (TYPE_1__*) ; 
 int PTR_ERR (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_err (TYPE_6__*,char*) ; 
 int /*<<< orphan*/  dev_warn (TYPE_6__*,char*) ; 
 struct isl1208_state* devm_kzalloc (TYPE_6__*,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* devm_rtc_allocate_device (TYPE_6__*) ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct isl1208_state*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 TYPE_5__* isl1208_configs ; 
 int isl1208_i2c_get_sr (struct i2c_client*) ; 
 scalar_t__ isl1208_i2c_validate_client (struct i2c_client*) ; 
 TYPE_3__ isl1208_nvmem_config ; 
 int /*<<< orphan*/  isl1208_rtc_ops ; 
 int /*<<< orphan*/  isl1208_rtc_sysfs_files ; 
 int isl1208_setup_irq (struct i2c_client*,int) ; 
 int /*<<< orphan*/  isl1219_rtc_sysfs_files ; 
 TYPE_5__* of_device_get_match_data (TYPE_6__*) ; 
 int of_irq_get_byname (struct device_node*,char*) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,scalar_t__*) ; 
 int rtc_add_group (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int rtc_nvmem_register (TYPE_1__*,TYPE_3__*) ; 
 int rtc_register_device (TYPE_1__*) ; 

__attribute__((used)) static int
isl1208_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	int rc = 0;
	struct isl1208_state *isl1208;
	int evdet_irq = -1;

	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C))
		return -ENODEV;

	if (isl1208_i2c_validate_client(client) < 0)
		return -ENODEV;

	/* Allocate driver state, point i2c client data to it */
	isl1208 = devm_kzalloc(&client->dev, sizeof(*isl1208), GFP_KERNEL);
	if (!isl1208)
		return -ENOMEM;
	i2c_set_clientdata(client, isl1208);

	/* Determine which chip we have */
	if (client->dev.of_node) {
		isl1208->config = of_device_get_match_data(&client->dev);
		if (!isl1208->config)
			return -ENODEV;
	} else {
		if (id->driver_data >= ISL_LAST_ID)
			return -ENODEV;
		isl1208->config = &isl1208_configs[id->driver_data];
	}

	isl1208->rtc = devm_rtc_allocate_device(&client->dev);
	if (IS_ERR(isl1208->rtc))
		return PTR_ERR(isl1208->rtc);

	isl1208->rtc->ops = &isl1208_rtc_ops;

	/* Setup nvmem configuration in driver state struct */
	isl1208->nvmem_config = isl1208_nvmem_config;
	isl1208->nvmem_config.size = isl1208->config->nvmem_length;
	isl1208->nvmem_config.priv = isl1208;

	rc = isl1208_i2c_get_sr(client);
	if (rc < 0) {
		dev_err(&client->dev, "reading status failed\n");
		return rc;
	}

	if (rc & ISL1208_REG_SR_RTCF)
		dev_warn(&client->dev, "rtc power failure detected, "
			 "please set clock.\n");

	if (isl1208->config->has_tamper) {
		struct device_node *np = client->dev.of_node;
		u32 evienb;

		rc = i2c_smbus_read_byte_data(client, ISL1219_REG_EV);
		if (rc < 0) {
			dev_err(&client->dev, "failed to read EV reg\n");
			return rc;
		}
		rc |= ISL1219_REG_EV_EVEN;
		if (!of_property_read_u32(np, "isil,ev-evienb", &evienb)) {
			if (evienb)
				rc |= ISL1219_REG_EV_EVIENB;
			else
				rc &= ~ISL1219_REG_EV_EVIENB;
		}
		rc = i2c_smbus_write_byte_data(client, ISL1219_REG_EV, rc);
		if (rc < 0) {
			dev_err(&client->dev, "could not enable tamper detection\n");
			return rc;
		}
		evdet_irq = of_irq_get_byname(np, "evdet");
	}
	if (isl1208->config->has_timestamp) {
		rc = rtc_add_group(isl1208->rtc, &isl1219_rtc_sysfs_files);
		if (rc)
			return rc;
	}

	rc = rtc_add_group(isl1208->rtc, &isl1208_rtc_sysfs_files);
	if (rc)
		return rc;

	if (client->irq > 0)
		rc = isl1208_setup_irq(client, client->irq);
	if (rc)
		return rc;

	if (evdet_irq > 0 && evdet_irq != client->irq)
		rc = isl1208_setup_irq(client, evdet_irq);
	if (rc)
		return rc;

	rc = rtc_nvmem_register(isl1208->rtc, &isl1208->nvmem_config);
	if (rc)
		return rc;

	return rtc_register_device(isl1208->rtc);
}