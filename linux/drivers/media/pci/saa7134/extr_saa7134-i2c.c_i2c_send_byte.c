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
typedef  enum i2c_attr { ____Placeholder_i2c_attr } i2c_attr ;
typedef  int __u32 ;

/* Variables and functions */
 int EIO ; 
 int SAA7134_I2C_ATTR_STATUS ; 
 int /*<<< orphan*/  i2c_dbg (int,char*,unsigned char) ; 
 int i2c_get_status (struct saa7134_dev*) ; 
 int /*<<< orphan*/  i2c_is_busy_wait (struct saa7134_dev*) ; 
 scalar_t__ i2c_is_error (int) ; 
 int saa_readl (int) ; 
 int /*<<< orphan*/  saa_writel (int,int) ; 

__attribute__((used)) static inline int i2c_send_byte(struct saa7134_dev *dev,
				enum i2c_attr attr,
				unsigned char data)
{
	enum i2c_status status;
	__u32 dword;

	/* have to write both attr + data in one 32bit word */
	dword  = saa_readl(SAA7134_I2C_ATTR_STATUS >> 2);
	dword &= 0x0f;
	dword |= (attr << 6);
	dword |= ((__u32)data << 8);
	dword |= 0x00 << 16;  /* 100 kHz */
//	dword |= 0x40 << 16;  /* 400 kHz */
	dword |= 0xf0 << 24;
	saa_writel(SAA7134_I2C_ATTR_STATUS >> 2, dword);
	i2c_dbg(2, "i2c data => 0x%x\n", data);

	if (!i2c_is_busy_wait(dev))
		return -EIO;
	status = i2c_get_status(dev);
	if (i2c_is_error(status))
		return -EIO;
	return 0;
}