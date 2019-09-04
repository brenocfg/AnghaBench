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
struct clock_event_device {int dummy; } ;

/* Variables and functions */
 unsigned int COUNTEN ; 
 unsigned int INTEN ; 
 unsigned int ONESHOT ; 
 unsigned int PRESCALE ; 
 int /*<<< orphan*/  REG_TCSR0 ; 
 int __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nuc900_clockevent_set_oneshot(struct clock_event_device *evt)
{
	unsigned int val = __raw_readl(REG_TCSR0) & ~(0x03 << 27);

	val |= (ONESHOT | COUNTEN | INTEN | PRESCALE);

	__raw_writel(val, REG_TCSR0);
	return 0;
}