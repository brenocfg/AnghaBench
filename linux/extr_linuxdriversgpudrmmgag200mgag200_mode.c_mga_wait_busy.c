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
struct mga_device {int dummy; } ;

/* Variables and functions */
 unsigned long HZ ; 
 scalar_t__ MGAREG_Status ; 
 unsigned int RREG8 (scalar_t__) ; 
 unsigned long jiffies ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static inline void mga_wait_busy(struct mga_device *mdev)
{
	unsigned long timeout = jiffies + HZ;
	unsigned int status = 0;
	do {
		status = RREG8(MGAREG_Status + 2);
	} while ((status & 0x01) && time_before(jiffies, timeout));
}