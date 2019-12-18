#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct flexcop_device {TYPE_3__* fc_i2c_adap; int /*<<< orphan*/  init_state; int /*<<< orphan*/  dev; int /*<<< orphan*/  i2c_mutex; } ;
struct TYPE_6__ {int /*<<< orphan*/  parent; } ;
struct TYPE_7__ {TYPE_1__ dev; int /*<<< orphan*/ * algo_data; int /*<<< orphan*/ * algo; int /*<<< orphan*/  name; } ;
struct TYPE_8__ {TYPE_2__ i2c_adap; int /*<<< orphan*/  port; struct flexcop_device* fc; } ;

/* Variables and functions */
 int /*<<< orphan*/  FC_I2C_PORT_DEMOD ; 
 int /*<<< orphan*/  FC_I2C_PORT_EEPROM ; 
 int /*<<< orphan*/  FC_I2C_PORT_TUNER ; 
 int /*<<< orphan*/  FC_STATE_I2C_INIT ; 
 int /*<<< orphan*/  flexcop_algo ; 
 int i2c_add_adapter (TYPE_2__*) ; 
 int /*<<< orphan*/  i2c_del_adapter (TYPE_2__*) ; 
 int /*<<< orphan*/  i2c_set_adapdata (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char*,int) ; 

int flexcop_i2c_init(struct flexcop_device *fc)
{
	int ret;
	mutex_init(&fc->i2c_mutex);

	fc->fc_i2c_adap[0].fc = fc;
	fc->fc_i2c_adap[1].fc = fc;
	fc->fc_i2c_adap[2].fc = fc;
	fc->fc_i2c_adap[0].port = FC_I2C_PORT_DEMOD;
	fc->fc_i2c_adap[1].port = FC_I2C_PORT_EEPROM;
	fc->fc_i2c_adap[2].port = FC_I2C_PORT_TUNER;

	strscpy(fc->fc_i2c_adap[0].i2c_adap.name, "B2C2 FlexCop I2C to demod",
		sizeof(fc->fc_i2c_adap[0].i2c_adap.name));
	strscpy(fc->fc_i2c_adap[1].i2c_adap.name, "B2C2 FlexCop I2C to eeprom",
		sizeof(fc->fc_i2c_adap[1].i2c_adap.name));
	strscpy(fc->fc_i2c_adap[2].i2c_adap.name, "B2C2 FlexCop I2C to tuner",
		sizeof(fc->fc_i2c_adap[2].i2c_adap.name));

	i2c_set_adapdata(&fc->fc_i2c_adap[0].i2c_adap, &fc->fc_i2c_adap[0]);
	i2c_set_adapdata(&fc->fc_i2c_adap[1].i2c_adap, &fc->fc_i2c_adap[1]);
	i2c_set_adapdata(&fc->fc_i2c_adap[2].i2c_adap, &fc->fc_i2c_adap[2]);

	fc->fc_i2c_adap[0].i2c_adap.algo =
		fc->fc_i2c_adap[1].i2c_adap.algo =
		fc->fc_i2c_adap[2].i2c_adap.algo = &flexcop_algo;
	fc->fc_i2c_adap[0].i2c_adap.algo_data =
		fc->fc_i2c_adap[1].i2c_adap.algo_data =
		fc->fc_i2c_adap[2].i2c_adap.algo_data = NULL;
	fc->fc_i2c_adap[0].i2c_adap.dev.parent =
		fc->fc_i2c_adap[1].i2c_adap.dev.parent =
		fc->fc_i2c_adap[2].i2c_adap.dev.parent = fc->dev;

	ret = i2c_add_adapter(&fc->fc_i2c_adap[0].i2c_adap);
	if (ret < 0)
		return ret;

	ret = i2c_add_adapter(&fc->fc_i2c_adap[1].i2c_adap);
	if (ret < 0)
		goto adap_1_failed;

	ret = i2c_add_adapter(&fc->fc_i2c_adap[2].i2c_adap);
	if (ret < 0)
		goto adap_2_failed;

	fc->init_state |= FC_STATE_I2C_INIT;
	return 0;

adap_2_failed:
	i2c_del_adapter(&fc->fc_i2c_adap[1].i2c_adap);
adap_1_failed:
	i2c_del_adapter(&fc->fc_i2c_adap[0].i2c_adap);
	return ret;
}