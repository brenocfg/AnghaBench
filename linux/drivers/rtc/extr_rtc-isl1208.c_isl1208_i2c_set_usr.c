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
typedef  int u16 ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISL1208_REG_USR1 ; 
 int ISL1208_USR_SECTION_LEN ; 
 int isl1208_i2c_set_regs (struct i2c_client*,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int
isl1208_i2c_set_usr(struct i2c_client *client, u16 usr)
{
	u8 buf[ISL1208_USR_SECTION_LEN];

	buf[0] = usr & 0xff;
	buf[1] = (usr >> 8) & 0xff;

	return isl1208_i2c_set_regs(client, ISL1208_REG_USR1, buf,
				    ISL1208_USR_SECTION_LEN);
}