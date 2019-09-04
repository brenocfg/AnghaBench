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
typedef  int /*<<< orphan*/  u16 ;
struct i2c_client {int dummy; } ;
typedef  enum g760a_regs { ____Placeholder_g760a_regs } g760a_regs ;

/* Variables and functions */
 int i2c_smbus_write_byte_data (struct i2c_client*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int g760a_write_value(struct i2c_client *client, enum g760a_regs reg,
			     u16 value)
{
	return i2c_smbus_write_byte_data(client, reg, value);
}