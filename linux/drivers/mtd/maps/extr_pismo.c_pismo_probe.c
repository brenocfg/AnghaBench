#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct pismo_pdata {int /*<<< orphan*/ * cs_addrs; int /*<<< orphan*/  vpp_data; int /*<<< orphan*/  set_vpp; } ;
struct pismo_eeprom {TYPE_1__* cs; int /*<<< orphan*/  board; } ;
struct pismo_data {int /*<<< orphan*/  vpp_data; int /*<<< orphan*/  vpp; struct i2c_client* client; } ;
struct i2c_device_id {int dummy; } ;
struct TYPE_6__ {struct pismo_pdata* platform_data; } ;
struct i2c_client {TYPE_2__ dev; int /*<<< orphan*/  adapter; } ;
typedef  int /*<<< orphan*/  eeprom ;
struct TYPE_5__ {int type; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_FUNC_I2C ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  dev_info (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct pismo_data*) ; 
 int /*<<< orphan*/  kfree (struct pismo_data*) ; 
 struct pismo_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pismo_add_one (struct pismo_data*,int,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int pismo_eeprom_read (struct i2c_client*,struct pismo_eeprom*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int pismo_probe(struct i2c_client *client,
		       const struct i2c_device_id *id)
{
	struct pismo_pdata *pdata = client->dev.platform_data;
	struct pismo_eeprom eeprom;
	struct pismo_data *pismo;
	int ret, i;

	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) {
		dev_err(&client->dev, "functionality mismatch\n");
		return -EIO;
	}

	pismo = kzalloc(sizeof(*pismo), GFP_KERNEL);
	if (!pismo)
		return -ENOMEM;

	pismo->client = client;
	if (pdata) {
		pismo->vpp = pdata->set_vpp;
		pismo->vpp_data = pdata->vpp_data;
	}
	i2c_set_clientdata(client, pismo);

	ret = pismo_eeprom_read(client, &eeprom, 0, sizeof(eeprom));
	if (ret < 0) {
		dev_err(&client->dev, "error reading EEPROM: %d\n", ret);
		goto exit_free;
	}

	dev_info(&client->dev, "%.15s board found\n", eeprom.board);

	for (i = 0; i < ARRAY_SIZE(eeprom.cs); i++)
		if (eeprom.cs[i].type != 0xff)
			pismo_add_one(pismo, i, &eeprom.cs[i],
				      pdata->cs_addrs[i]);

	return 0;

 exit_free:
	kfree(pismo);
	return ret;
}