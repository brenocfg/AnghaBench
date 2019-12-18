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
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_PREFIX_NONE ; 
 int i2c_master_recv (struct i2c_client*,unsigned char*,int) ; 
 int i2c_master_send (struct i2c_client*,unsigned char*,int) ; 
 int /*<<< orphan*/  pr_info (char*,int) ; 
 int /*<<< orphan*/  pr_warn (char*,int) ; 
 int /*<<< orphan*/  print_hex_dump_debug (char*,int /*<<< orphan*/ ,int,int,unsigned char*,int,int) ; 

int tveeprom_read(struct i2c_client *c, unsigned char *eedata, int len)
{
	unsigned char buf;
	int err;

	buf = 0;
	err = i2c_master_send(c, &buf, 1);
	if (err != 1) {
		pr_info("Huh, no eeprom present (err=%d)?\n", err);
		return -1;
	}
	err = i2c_master_recv(c, eedata, len);
	if (err != len) {
		pr_warn("i2c eeprom read error (err=%d)\n", err);
		return -1;
	}

	print_hex_dump_debug("full 256-byte eeprom dump:", DUMP_PREFIX_NONE,
			     16, 1, eedata, len, true);
	return 0;
}