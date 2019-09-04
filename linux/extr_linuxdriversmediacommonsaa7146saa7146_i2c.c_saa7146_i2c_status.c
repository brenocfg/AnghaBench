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
typedef  int /*<<< orphan*/  u32 ;
struct saa7146_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_STATUS ; 
 int /*<<< orphan*/  saa7146_read (struct saa7146_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 saa7146_i2c_status(struct saa7146_dev *dev)
{
	u32 iicsta = saa7146_read(dev, I2C_STATUS);
	/* DEB_I2C("status: 0x%08x\n", iicsta); */
	return iicsta;
}