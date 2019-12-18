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
typedef  enum i2c_status { ____Placeholder_i2c_status } i2c_status ;

/* Variables and functions */
 int /*<<< orphan*/  SAA7134_I2C_ATTR_STATUS ; 
 int /*<<< orphan*/  i2c_dbg (int,char*,int /*<<< orphan*/ ) ; 
 int saa_readb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * str_i2c_status ; 

__attribute__((used)) static inline enum i2c_status i2c_get_status(struct saa7134_dev *dev)
{
	enum i2c_status status;

	status = saa_readb(SAA7134_I2C_ATTR_STATUS) & 0x0f;
	i2c_dbg(2, "i2c stat <= %s\n", str_i2c_status[status]);
	return status;
}