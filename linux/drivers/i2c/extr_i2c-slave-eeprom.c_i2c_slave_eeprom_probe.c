#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct i2c_device_id {int /*<<< orphan*/  driver_data; } ;
struct TYPE_8__ {int /*<<< orphan*/  kobj; } ;
struct i2c_client {TYPE_5__ dev; } ;
struct TYPE_6__ {char* name; int mode; } ;
struct TYPE_7__ {unsigned int size; int /*<<< orphan*/  write; int /*<<< orphan*/  read; TYPE_1__ attr; } ;
struct eeprom_data {int num_address_bytes; unsigned int address_mask; TYPE_2__ bin; int /*<<< orphan*/  buffer_lock; void* read_only; scalar_t__ idx_write_cnt; } ;

/* Variables and functions */
 int ENOMEM ; 
 void* FIELD_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_SLAVE_BYTELEN ; 
 int /*<<< orphan*/  I2C_SLAVE_FLAG_ADDR16 ; 
 int /*<<< orphan*/  I2C_SLAVE_FLAG_RO ; 
 int S_IRUSR ; 
 int S_IWUSR ; 
 struct eeprom_data* devm_kzalloc (TYPE_5__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct eeprom_data*) ; 
 int /*<<< orphan*/  i2c_slave_eeprom_bin_read ; 
 int /*<<< orphan*/  i2c_slave_eeprom_bin_write ; 
 int /*<<< orphan*/  i2c_slave_eeprom_slave_cb ; 
 int i2c_slave_register (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_bin_attr_init (TYPE_2__*) ; 
 int sysfs_create_bin_file (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  sysfs_remove_bin_file (int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static int i2c_slave_eeprom_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	struct eeprom_data *eeprom;
	int ret;
	unsigned int size = FIELD_GET(I2C_SLAVE_BYTELEN, id->driver_data);
	unsigned int flag_addr16 = FIELD_GET(I2C_SLAVE_FLAG_ADDR16, id->driver_data);

	eeprom = devm_kzalloc(&client->dev, sizeof(struct eeprom_data) + size, GFP_KERNEL);
	if (!eeprom)
		return -ENOMEM;

	eeprom->idx_write_cnt = 0;
	eeprom->num_address_bytes = flag_addr16 ? 2 : 1;
	eeprom->address_mask = size - 1;
	eeprom->read_only = FIELD_GET(I2C_SLAVE_FLAG_RO, id->driver_data);
	spin_lock_init(&eeprom->buffer_lock);
	i2c_set_clientdata(client, eeprom);

	sysfs_bin_attr_init(&eeprom->bin);
	eeprom->bin.attr.name = "slave-eeprom";
	eeprom->bin.attr.mode = S_IRUSR | S_IWUSR;
	eeprom->bin.read = i2c_slave_eeprom_bin_read;
	eeprom->bin.write = i2c_slave_eeprom_bin_write;
	eeprom->bin.size = size;

	ret = sysfs_create_bin_file(&client->dev.kobj, &eeprom->bin);
	if (ret)
		return ret;

	ret = i2c_slave_register(client, i2c_slave_eeprom_slave_cb);
	if (ret) {
		sysfs_remove_bin_file(&client->dev.kobj, &eeprom->bin);
		return ret;
	}

	return 0;
}