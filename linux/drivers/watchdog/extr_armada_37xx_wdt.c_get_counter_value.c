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
typedef  int u64 ;
struct armada_37xx_watchdog {scalar_t__ reg; } ;

/* Variables and functions */
 scalar_t__ CNTR_COUNT_HIGH (int) ; 
 scalar_t__ CNTR_COUNT_LOW (int) ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static u64 get_counter_value(struct armada_37xx_watchdog *dev, int id)
{
	u64 val;

	/*
	 * when low is read, high is latched into flip-flops so that it can be
	 * read consistently without using software debouncing
	 */
	val = readl(dev->reg + CNTR_COUNT_LOW(id));
	val |= ((u64)readl(dev->reg + CNTR_COUNT_HIGH(id))) << 32;

	return val;
}