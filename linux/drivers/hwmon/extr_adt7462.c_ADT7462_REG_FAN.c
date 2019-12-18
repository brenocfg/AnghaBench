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
 int ADT7462_REG_FAN2_BASE_ADDR ; 
 int ADT7462_REG_FAN_BASE_ADDR ; 

__attribute__((used)) static int ADT7462_REG_FAN(int fan)
{
	if (fan < 4)
		return ADT7462_REG_FAN_BASE_ADDR + (2 * fan);
	return ADT7462_REG_FAN2_BASE_ADDR + (2 * (fan - 4));
}