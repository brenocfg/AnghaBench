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
 scalar_t__ SIRFSOC_TIMER_32COUNTER_0_CTRL ; 
 int readl_relaxed (scalar_t__) ; 
 scalar_t__ sirfsoc_timer_base ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static inline void sirfsoc_timer_count_disable(int idx)
{
	writel_relaxed(readl_relaxed(sirfsoc_timer_base + SIRFSOC_TIMER_32COUNTER_0_CTRL + 4 * idx) & ~0x7,
		sirfsoc_timer_base + SIRFSOC_TIMER_32COUNTER_0_CTRL + 4 * idx);
}