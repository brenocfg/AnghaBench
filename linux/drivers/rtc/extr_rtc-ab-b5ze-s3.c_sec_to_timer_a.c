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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int /*<<< orphan*/  ABB5ZES3_REG_TIMA_CLK_TAQ1 ; 

__attribute__((used)) static inline void sec_to_timer_a(u8 secs, u8 *taq, u8 *timer_a)
{
	*taq = ABB5ZES3_REG_TIMA_CLK_TAQ1; /* 1Hz */
	*timer_a = secs;
}