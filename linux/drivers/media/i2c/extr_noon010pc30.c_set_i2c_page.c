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
typedef  scalar_t__ u32 ;
struct noon010_info {scalar_t__ i2c_reg_page; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGEMODE_REG ; 
 int i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline int set_i2c_page(struct noon010_info *info,
			       struct i2c_client *client, unsigned int reg)
{
	u32 page = reg >> 8 & 0xFF;
	int ret = 0;

	if (info->i2c_reg_page != page && (reg & 0xFF) != 0x03) {
		ret = i2c_smbus_write_byte_data(client, PAGEMODE_REG, page);
		if (!ret)
			info->i2c_reg_page = page;
	}
	return ret;
}