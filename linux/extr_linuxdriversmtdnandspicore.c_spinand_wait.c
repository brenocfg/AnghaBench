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
struct spinand_device {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int STATUS_BUSY ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 int spinand_read_status (struct spinand_device*,int*) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static int spinand_wait(struct spinand_device *spinand, u8 *s)
{
	unsigned long timeo =  jiffies + msecs_to_jiffies(400);
	u8 status;
	int ret;

	do {
		ret = spinand_read_status(spinand, &status);
		if (ret)
			return ret;

		if (!(status & STATUS_BUSY))
			goto out;
	} while (time_before(jiffies, timeo));

	/*
	 * Extra read, just in case the STATUS_READY bit has changed
	 * since our last check
	 */
	ret = spinand_read_status(spinand, &status);
	if (ret)
		return ret;

out:
	if (s)
		*s = status;

	return status & STATUS_BUSY ? -ETIMEDOUT : 0;
}