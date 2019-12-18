#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct isl1208_state {TYPE_2__* rtc; } ;
struct i2c_client {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 scalar_t__ ISL1208_REG_USR1 ; 
 int isl1208_i2c_set_regs (struct i2c_client*,scalar_t__,void*,size_t) ; 
 struct i2c_client* to_i2c_client (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int isl1208_nvmem_write(void *priv, unsigned int off, void *buf,
			       size_t count)
{
	struct isl1208_state *isl1208 = priv;
	struct i2c_client *client = to_i2c_client(isl1208->rtc->dev.parent);
	int ret;

	/* nvmem sanitizes off/count for us, but count==0 is possible */
	if (!count)
		return count;
	ret = isl1208_i2c_set_regs(client, ISL1208_REG_USR1 + off, buf,
				   count);

	return ret == 0 ? count : ret;
}