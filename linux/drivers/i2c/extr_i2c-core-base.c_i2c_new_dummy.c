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
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct i2c_client*) ; 
 struct i2c_client* i2c_new_dummy_device (struct i2c_adapter*,int /*<<< orphan*/ ) ; 

struct i2c_client *i2c_new_dummy(struct i2c_adapter *adapter, u16 address)
{
	struct i2c_client *ret;

	ret = i2c_new_dummy_device(adapter, address);
	return IS_ERR(ret) ? NULL : ret;
}