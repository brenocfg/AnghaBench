#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct stv090x_dev {struct stv090x_dev* next_dev; TYPE_1__* internal; } ;
struct i2c_adapter {int dummy; } ;
struct TYPE_2__ {scalar_t__ i2c_addr; struct i2c_adapter* i2c_adap; } ;

/* Variables and functions */
 struct stv090x_dev* stv090x_first_dev ; 

__attribute__((used)) static struct stv090x_dev *find_dev(struct i2c_adapter *i2c_adap,
					u8 i2c_addr)
{
	struct stv090x_dev *temp_dev = stv090x_first_dev;

	/*
	 Search of the last stv0900 chip or
	 find it by i2c adapter and i2c address */
	while ((temp_dev != NULL) &&
		((temp_dev->internal->i2c_adap != i2c_adap) ||
		(temp_dev->internal->i2c_addr != i2c_addr))) {

		temp_dev = temp_dev->next_dev;
	}

	return temp_dev;
}