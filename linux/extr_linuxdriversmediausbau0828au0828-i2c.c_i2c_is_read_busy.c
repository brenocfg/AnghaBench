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
struct i2c_adapter {struct au0828_dev* algo_data; } ;
struct au0828_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AU0828_I2C_STATUS_201 ; 
 int AU0828_I2C_STATUS_READ_DONE ; 
 int au0828_read (struct au0828_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int i2c_is_read_busy(struct i2c_adapter *i2c_adap)
{
	struct au0828_dev *dev = i2c_adap->algo_data;
	return au0828_read(dev, AU0828_I2C_STATUS_201) &
		AU0828_I2C_STATUS_READ_DONE ? 0 : 1;
}