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
 int ENODATA ; 
 int ENOTSUPP ; 
 int MAX31785_NR_PAGES ; 
#define  PMBUS_FAN_CONFIG_12 129 
#define  PMBUS_VOUT_MODE 128 
 int pmbus_read_byte_data (struct i2c_client*,int,int) ; 

__attribute__((used)) static int max31785_read_byte_data(struct i2c_client *client, int page,
				   int reg)
{
	if (page < MAX31785_NR_PAGES)
		return -ENODATA;

	switch (reg) {
	case PMBUS_VOUT_MODE:
		return -ENOTSUPP;
	case PMBUS_FAN_CONFIG_12:
		return pmbus_read_byte_data(client, page - MAX31785_NR_PAGES,
					    reg);
	}

	return -ENODATA;
}