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
struct NCR5380_hostdata {unsigned long poll_loops; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int NCR5380_read (unsigned int) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 scalar_t__ in_interrupt () ; 
 scalar_t__ irqs_disabled () ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  schedule_timeout_uninterruptible (int) ; 
 scalar_t__ time_is_after_jiffies (unsigned long) ; 

__attribute__((used)) static int NCR5380_poll_politely2(struct NCR5380_hostdata *hostdata,
                                  unsigned int reg1, u8 bit1, u8 val1,
                                  unsigned int reg2, u8 bit2, u8 val2,
                                  unsigned long wait)
{
	unsigned long n = hostdata->poll_loops;
	unsigned long deadline = jiffies + wait;

	do {
		if ((NCR5380_read(reg1) & bit1) == val1)
			return 0;
		if ((NCR5380_read(reg2) & bit2) == val2)
			return 0;
		cpu_relax();
	} while (n--);

	if (irqs_disabled() || in_interrupt())
		return -ETIMEDOUT;

	/* Repeatedly sleep for 1 ms until deadline */
	while (time_is_after_jiffies(deadline)) {
		schedule_timeout_uninterruptible(1);
		if ((NCR5380_read(reg1) & bit1) == val1)
			return 0;
		if ((NCR5380_read(reg2) & bit2) == val2)
			return 0;
	}

	return -ETIMEDOUT;
}