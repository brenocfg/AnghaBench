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
typedef  int u8 ;
struct kobject {int dummy; } ;
struct i2c_client {int dummy; } ;
struct file {int dummy; } ;
struct eeprom_data {scalar_t__ nature; char* data; } ;
struct bin_attribute {int dummy; } ;
typedef  size_t ssize_t ;
typedef  int loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 scalar_t__ VAIO ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eeprom_update_client (struct i2c_client*,int) ; 
 struct eeprom_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  kobj_to_dev (struct kobject*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 struct i2c_client* to_i2c_client (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t eeprom_read(struct file *filp, struct kobject *kobj,
			   struct bin_attribute *bin_attr,
			   char *buf, loff_t off, size_t count)
{
	struct i2c_client *client = to_i2c_client(kobj_to_dev(kobj));
	struct eeprom_data *data = i2c_get_clientdata(client);
	u8 slice;

	/* Only refresh slices which contain requested bytes */
	for (slice = off >> 5; slice <= (off + count - 1) >> 5; slice++)
		eeprom_update_client(client, slice);

	/* Hide Vaio private settings to regular users:
	   - BIOS passwords: bytes 0x00 to 0x0f
	   - UUID: bytes 0x10 to 0x1f
	   - Serial number: 0xc0 to 0xdf */
	if (data->nature == VAIO && !capable(CAP_SYS_ADMIN)) {
		int i;

		for (i = 0; i < count; i++) {
			if ((off + i <= 0x1f) ||
			    (off + i >= 0xc0 && off + i <= 0xdf))
				buf[i] = 0;
			else
				buf[i] = data->data[off + i];
		}
	} else {
		memcpy(buf, &data->data[off], count);
	}

	return count;
}