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
struct cx25821_dev {int tvnorm; int /*<<< orphan*/ * i2c_bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  DENC_A_REG_4 ; 
 int /*<<< orphan*/  DENC_B_REG_4 ; 
 int V4L2_STD_PAL_BG ; 
 int V4L2_STD_PAL_DK ; 
 int /*<<< orphan*/  cx25821_i2c_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int cx25821_i2c_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int medusa_initialize_ntsc (struct cx25821_dev*) ; 
 int medusa_initialize_pal (struct cx25821_dev*) ; 
 int /*<<< orphan*/  setBitAtPos (int /*<<< orphan*/ ,int) ; 

int medusa_set_videostandard(struct cx25821_dev *dev)
{
	int status = 0;
	u32 value = 0, tmp = 0;

	if (dev->tvnorm & V4L2_STD_PAL_BG || dev->tvnorm & V4L2_STD_PAL_DK)
		status = medusa_initialize_pal(dev);
	else
		status = medusa_initialize_ntsc(dev);

	/* Enable DENC_A output */
	value = cx25821_i2c_read(&dev->i2c_bus[0], DENC_A_REG_4, &tmp);
	value = setBitAtPos(value, 4);
	status = cx25821_i2c_write(&dev->i2c_bus[0], DENC_A_REG_4, value);

	/* Enable DENC_B output */
	value = cx25821_i2c_read(&dev->i2c_bus[0], DENC_B_REG_4, &tmp);
	value = setBitAtPos(value, 4);
	status = cx25821_i2c_write(&dev->i2c_bus[0], DENC_B_REG_4, value);

	return status;
}