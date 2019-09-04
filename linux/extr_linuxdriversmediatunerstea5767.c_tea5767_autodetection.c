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
typedef  int /*<<< orphan*/  u8 ;
struct tuner_i2c_props {int /*<<< orphan*/  addr; struct i2c_adapter* adap; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  pr_warn (char*,...) ; 
 int tuner_i2c_xfer_recv (struct tuner_i2c_props*,unsigned char*,int) ; 

int tea5767_autodetection(struct i2c_adapter* i2c_adap, u8 i2c_addr)
{
	struct tuner_i2c_props i2c = { .adap = i2c_adap, .addr = i2c_addr };
	unsigned char buffer[7] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };

	int rc;

	if ((rc = tuner_i2c_xfer_recv(&i2c, buffer, 7))< 5) {
		pr_warn("It is not a TEA5767. Received %i bytes.\n", rc);
		return -EINVAL;
	}

	/* If all bytes are the same then it's a TV tuner and not a tea5767 */
	if (buffer[0] == buffer[1] && buffer[0] == buffer[2] &&
	    buffer[0] == buffer[3] && buffer[0] == buffer[4]) {
		pr_warn("All bytes are equal. It is not a TEA5767\n");
		return -EINVAL;
	}

	/*  Status bytes:
	 *  Byte 4: bit 3:1 : CI (Chip Identification) == 0
	 *          bit 0   : internally set to 0
	 *  Byte 5: bit 7:0 : == 0
	 */
	if (((buffer[3] & 0x0f) != 0x00) || (buffer[4] != 0x00)) {
		pr_warn("Chip ID is not zero. It is not a TEA5767\n");
		return -EINVAL;
	}


	return 0;
}