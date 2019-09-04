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
typedef  int u8 ;
typedef  int u32 ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int M5MOLS_BUSY_WAIT_DEF_TIMEOUT ; 
 int M5MOLS_I2C_RDY_WAIT_FL ; 
 unsigned long jiffies ; 
 int m5mols_read_u8 (struct v4l2_subdev*,int,int*) ; 
 unsigned long msecs_to_jiffies (int) ; 
 scalar_t__ time_is_after_jiffies (unsigned long) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

int m5mols_busy_wait(struct v4l2_subdev *sd, u32 reg, u32 value, u32 mask,
		     int timeout)
{
	int ms = timeout < 0 ? M5MOLS_BUSY_WAIT_DEF_TIMEOUT : timeout;
	unsigned long end = jiffies + msecs_to_jiffies(ms);
	u8 status;

	do {
		int ret = m5mols_read_u8(sd, reg, &status);

		if (ret < 0 && !(mask & M5MOLS_I2C_RDY_WAIT_FL))
			return ret;
		if (!ret && (status & mask & 0xff) == (value & 0xff))
			return 0;
		usleep_range(100, 250);
	} while (ms > 0 && time_is_after_jiffies(end));

	return -EBUSY;
}