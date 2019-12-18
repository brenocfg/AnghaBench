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
typedef  scalar_t__ u8 ;

/* Variables and functions */
 scalar_t__ ABB5ZES3_REG_TIMA_CLK_TAQ1 ; 
 int EINVAL ; 

__attribute__((used)) static inline int sec_from_timer_a(u8 *secs, u8 taq, u8 timer_a)
{
	if (taq != ABB5ZES3_REG_TIMA_CLK_TAQ1) /* 1Hz */
		return -EINVAL;

	*secs = timer_a;

	return 0;
}