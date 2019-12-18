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
struct pmic_wrapper {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 unsigned long jiffies ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 unsigned long usecs_to_jiffies (int) ; 

__attribute__((used)) static int pwrap_wait_for_state(struct pmic_wrapper *wrp,
		bool (*fp)(struct pmic_wrapper *))
{
	unsigned long timeout;

	timeout = jiffies + usecs_to_jiffies(10000);

	do {
		if (time_after(jiffies, timeout))
			return fp(wrp) ? 0 : -ETIMEDOUT;
		if (fp(wrp))
			return 0;
	} while (1);
}