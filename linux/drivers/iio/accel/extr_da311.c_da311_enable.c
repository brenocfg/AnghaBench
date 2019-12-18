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
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA311_REG_TEMP_CFG_REG ; 
 int da311_register_mask_write (struct i2c_client*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int da311_enable(struct i2c_client *client, bool enable)
{
	u8 data = enable ? 0x00 : 0x20;

	return da311_register_mask_write(client, DA311_REG_TEMP_CFG_REG,
					 0x20, data);
}