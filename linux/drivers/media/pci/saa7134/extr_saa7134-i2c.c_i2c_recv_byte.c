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
 int /*<<< orphan*/  CONTINUE ; 
 int EIO ; 
 int /*<<< orphan*/  SAA7134_I2C_DATA ; 
 int /*<<< orphan*/  i2c_dbg (int,char*,unsigned char) ; 
 int i2c_get_status (struct saa7134_dev*) ; 
 int /*<<< orphan*/  i2c_is_busy_wait (struct saa7134_dev*) ; 
 scalar_t__ i2c_is_error (int) ; 
 int /*<<< orphan*/  i2c_set_attr (struct saa7134_dev*,int /*<<< orphan*/ ) ; 
 unsigned char saa_readb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int i2c_recv_byte(struct saa7134_dev *dev)
{
	enum i2c_status status;
	unsigned char data;

	i2c_set_attr(dev,CONTINUE);
	if (!i2c_is_busy_wait(dev))
		return -EIO;
	status = i2c_get_status(dev);
	if (i2c_is_error(status))
		return -EIO;
	data = saa_readb(SAA7134_I2C_DATA);
	i2c_dbg(2, "i2c data <= 0x%x\n", data);
	return data;
}