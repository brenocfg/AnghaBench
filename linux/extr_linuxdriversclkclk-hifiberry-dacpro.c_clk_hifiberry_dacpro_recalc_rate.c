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
struct clk_hw {int dummy; } ;
struct TYPE_2__ {scalar_t__ mode; } ;

/* Variables and functions */
 unsigned long CLK_44EN_RATE ; 
 unsigned long CLK_48EN_RATE ; 
 TYPE_1__* to_hifiberry_clk (struct clk_hw*) ; 

__attribute__((used)) static unsigned long clk_hifiberry_dacpro_recalc_rate(struct clk_hw *hw,
	unsigned long parent_rate)
{
	return (to_hifiberry_clk(hw)->mode == 0) ? CLK_44EN_RATE :
		CLK_48EN_RATE;
}