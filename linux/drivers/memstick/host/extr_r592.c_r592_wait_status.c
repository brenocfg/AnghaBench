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
typedef  int u32 ;
struct r592_device {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int ETIME ; 
 int /*<<< orphan*/  R592_STATUS ; 
 int R592_STATUS_RECV_ERR ; 
 int R592_STATUS_SEND_ERR ; 
 int /*<<< orphan*/  cpu_relax () ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 int r592_read_reg (struct r592_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static int r592_wait_status(struct r592_device *dev, u32 mask, u32 wanted_mask)
{
	unsigned long timeout = jiffies + msecs_to_jiffies(1000);
	u32 reg = r592_read_reg(dev, R592_STATUS);

	if ((reg & mask) == wanted_mask)
		return 0;

	while (time_before(jiffies, timeout)) {

		reg = r592_read_reg(dev, R592_STATUS);

		if ((reg & mask) == wanted_mask)
			return 0;

		if (reg & (R592_STATUS_SEND_ERR | R592_STATUS_RECV_ERR))
			return -EIO;

		cpu_relax();
	}
	return -ETIME;
}