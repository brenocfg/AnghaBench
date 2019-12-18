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
 size_t SR_FROM_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * tach_period ; 

__attribute__((used)) static u8 get_tach_period(u8 fan_dynamics)
{
	return tach_period[SR_FROM_REG(fan_dynamics)];
}