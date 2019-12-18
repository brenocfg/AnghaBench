#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct si2157_config {struct dvb_frontend* fe; } ;
struct saa7164_port {struct i2c_client* i2c_client_tuner; } ;
struct TYPE_4__ {TYPE_1__* driver; } ;
struct i2c_client {TYPE_2__ dev; } ;
struct i2c_board_info {int addr; int /*<<< orphan*/  type; struct si2157_config* platform_data; } ;
struct i2c_adapter {int dummy; } ;
struct dvb_frontend {int dummy; } ;
typedef  int /*<<< orphan*/  bi ;
struct TYPE_3__ {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  I2C_NAME_SIZE ; 
 struct i2c_client* i2c_new_device (struct i2c_adapter*,struct i2c_board_info*) ; 
 int /*<<< orphan*/  i2c_unregister_device (struct i2c_client*) ; 
 int /*<<< orphan*/  memset (struct i2c_board_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  request_module (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int si2157_attach(struct saa7164_port *port, struct i2c_adapter *adapter,
	struct dvb_frontend *fe, u8 addr8bit, struct si2157_config *cfg)
{
	struct i2c_board_info bi;
	struct i2c_client *tuner;

	cfg->fe = fe;

	memset(&bi, 0, sizeof(bi));

	strscpy(bi.type, "si2157", I2C_NAME_SIZE);
	bi.platform_data = cfg;
	bi.addr = addr8bit >> 1;

	request_module(bi.type);

	tuner = i2c_new_device(adapter, &bi);
	if (tuner == NULL || tuner->dev.driver == NULL)
		return -ENODEV;

	if (!try_module_get(tuner->dev.driver->owner)) {
		i2c_unregister_device(tuner);
		return -ENODEV;
	}

	port->i2c_client_tuner = tuner;

	return 0;
}