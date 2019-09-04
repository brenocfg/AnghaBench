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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 scalar_t__ L2X0_EVENT_CNT0_VAL ; 
 scalar_t__ l2x0_base ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void l2x0_pmu_counter_write(int idx, u32 val)
{
	writel_relaxed(val, l2x0_base + L2X0_EVENT_CNT0_VAL - 4 * idx);
}