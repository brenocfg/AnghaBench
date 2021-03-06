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
struct saa7134_dev {int dummy; } ;
typedef  enum i2c_attr { ____Placeholder_i2c_attr } i2c_attr ;

/* Variables and functions */
 int /*<<< orphan*/  SAA7134_I2C_ATTR_STATUS ; 
 int /*<<< orphan*/  i2c_dbg (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saa_andorb (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/ * str_i2c_attr ; 

__attribute__((used)) static inline void i2c_set_attr(struct saa7134_dev *dev, enum i2c_attr attr)
{
	i2c_dbg(2, "i2c attr => %s\n", str_i2c_attr[attr]);
	saa_andorb(SAA7134_I2C_ATTR_STATUS,0xc0,attr << 6);
}