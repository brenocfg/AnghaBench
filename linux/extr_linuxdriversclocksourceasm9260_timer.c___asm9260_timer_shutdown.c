#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct clock_event_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  BM_C0_EN ; 
 scalar_t__ CLR_REG ; 
 scalar_t__ HW_TCR ; 
 TYPE_1__ priv ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void __asm9260_timer_shutdown(struct clock_event_device *evt)
{
	/* stop timer0 */
	writel_relaxed(BM_C0_EN, priv.base + HW_TCR + CLR_REG);
}