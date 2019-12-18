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
struct axxia_i2c_dev {scalar_t__ base; } ;

/* Variables and functions */
 int CMD_BUSY ; 
 int ETIMEDOUT ; 
 unsigned long I2C_XFER_TIMEOUT ; 
 scalar_t__ MST_COMMAND ; 
 unsigned long jiffies ; 
 int readl (scalar_t__) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int axxia_i2c_handle_seq_nak(struct axxia_i2c_dev *idev)
{
	unsigned long timeout = jiffies + I2C_XFER_TIMEOUT;

	do {
		if ((readl(idev->base + MST_COMMAND) & CMD_BUSY) == 0)
			return 0;
		usleep_range(1, 100);
	} while (time_before(jiffies, timeout));

	return -ETIMEDOUT;
}