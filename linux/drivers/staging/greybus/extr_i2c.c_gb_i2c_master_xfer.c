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
struct i2c_msg {int dummy; } ;
struct i2c_adapter {int dummy; } ;
struct gb_i2c_device {int dummy; } ;

/* Variables and functions */
 int gb_i2c_transfer_operation (struct gb_i2c_device*,struct i2c_msg*,int) ; 
 struct gb_i2c_device* i2c_get_adapdata (struct i2c_adapter*) ; 

__attribute__((used)) static int gb_i2c_master_xfer(struct i2c_adapter *adap, struct i2c_msg *msgs,
			      int msg_count)
{
	struct gb_i2c_device *gb_i2c_dev;

	gb_i2c_dev = i2c_get_adapdata(adap);

	return gb_i2c_transfer_operation(gb_i2c_dev, msgs, msg_count);
}