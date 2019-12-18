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

/* Variables and functions */
 int /*<<< orphan*/  REG_CMDBUF0_ADDR ; 
 int /*<<< orphan*/  REG_CMDWR_ADDRL ; 
 int s5k6aa_i2c_write (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s5k6aa_write(struct i2c_client *c, u16 addr, u16 val)
{
	int ret = s5k6aa_i2c_write(c, REG_CMDWR_ADDRL, addr);
	if (ret)
		return ret;
	return s5k6aa_i2c_write(c, REG_CMDBUF0_ADDR, val);
}