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
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int ARIZONA_REG_POLL_DELAY_US ; 
 scalar_t__ ktime_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static inline bool arizona_poll_reg_delay(ktime_t timeout)
{
	if (ktime_compare(ktime_get(), timeout) > 0)
		return false;

	usleep_range(ARIZONA_REG_POLL_DELAY_US / 2, ARIZONA_REG_POLL_DELAY_US);

	return true;
}