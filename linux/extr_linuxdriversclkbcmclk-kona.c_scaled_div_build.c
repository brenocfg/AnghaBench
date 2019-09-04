#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
struct TYPE_3__ {int frac_width; } ;
struct TYPE_4__ {TYPE_1__ s; } ;
struct bcm_clk_div {TYPE_2__ u; } ;

/* Variables and functions */
 int BILLION ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int DIV_ROUND_CLOSEST_ULL (int,int) ; 

u64 scaled_div_build(struct bcm_clk_div *div, u32 div_value, u32 billionths)
{
	u64 combined;

	BUG_ON(!div_value);
	BUG_ON(billionths >= BILLION);

	combined = (u64)div_value * BILLION + billionths;
	combined <<= div->u.s.frac_width;

	return DIV_ROUND_CLOSEST_ULL(combined, BILLION);
}