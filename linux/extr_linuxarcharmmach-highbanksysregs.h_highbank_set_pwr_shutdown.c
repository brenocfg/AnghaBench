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

/* Variables and functions */
 int /*<<< orphan*/  HB_PWR_SHUTDOWN ; 
 scalar_t__ HB_SREG_A9_PWR_REQ ; 
 int /*<<< orphan*/  highbank_set_core_pwr () ; 
 scalar_t__ sregs_base ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void highbank_set_pwr_shutdown(void)
{
	writel(HB_PWR_SHUTDOWN, sregs_base + HB_SREG_A9_PWR_REQ);
	highbank_set_core_pwr();
}