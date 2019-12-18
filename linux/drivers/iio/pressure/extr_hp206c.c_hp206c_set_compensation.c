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
 int HP206C_FLAG_CMPS_EN ; 
 int /*<<< orphan*/  HP206C_REG_PARA ; 
 int hp206c_read_reg (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int hp206c_write_reg (struct i2c_client*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hp206c_set_compensation(struct i2c_client *client, bool enabled)
{
	int val;

	val = hp206c_read_reg(client, HP206C_REG_PARA);
	if (val < 0)
		return val;
	if (enabled)
		val |= HP206C_FLAG_CMPS_EN;
	else
		val &= ~HP206C_FLAG_CMPS_EN;

	return hp206c_write_reg(client, HP206C_REG_PARA, val);
}