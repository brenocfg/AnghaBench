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
 int ENODEV ; 
#define  TSL45311_ID 131 
#define  TSL45313_ID 130 
#define  TSL45315_ID 129 
#define  TSL45317_ID 128 
 int /*<<< orphan*/  TSL4531_ID ; 
 int TSL4531_ID_SHIFT ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tsl4531_check_id(struct i2c_client *client)
{
	int ret = i2c_smbus_read_byte_data(client, TSL4531_ID);
	if (ret < 0)
		return ret;

	switch (ret >> TSL4531_ID_SHIFT) {
	case TSL45311_ID:
	case TSL45313_ID:
	case TSL45315_ID:
	case TSL45317_ID:
		return 0;
	default:
		return -ENODEV;
	}
}