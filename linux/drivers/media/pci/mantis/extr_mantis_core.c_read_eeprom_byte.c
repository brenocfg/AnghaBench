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
struct mantis_pci {int /*<<< orphan*/  adapter; } ;
struct i2c_msg {int addr; int* buf; int len; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_M_RD ; 
 int /*<<< orphan*/  MANTIS_ERROR ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int,int,int) ; 
 int i2c_transfer (int /*<<< orphan*/ *,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  verbose ; 

__attribute__((used)) static int read_eeprom_byte(struct mantis_pci *mantis, u8 *data, u8 length)
{
	int err;
	struct i2c_msg msg[] = {
		{
			.addr = 0x50,
			.flags = 0,
			.buf = data,
			.len = 1
		}, {
			.addr = 0x50,
			.flags = I2C_M_RD,
			.buf = data,
			.len = length
		},
	};

	err = i2c_transfer(&mantis->adapter, msg, 2);
	if (err < 0) {
		dprintk(verbose, MANTIS_ERROR, 1,
			"ERROR: i2c read: < err=%i d0=0x%02x d1=0x%02x >",
			err, data[0], data[1]);

		return err;
	}

	return 0;
}