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
 int /*<<< orphan*/  DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 
 int OV2685_XVCLK_FREQ ; 

__attribute__((used)) static inline u32 ov2685_cal_delay(u32 cycles)
{
	return DIV_ROUND_UP(cycles, OV2685_XVCLK_FREQ / 1000 / 1000);
}