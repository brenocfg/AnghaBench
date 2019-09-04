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
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {scalar_t__ frac_width; } ;
struct TYPE_4__ {TYPE_1__ s; } ;
struct bcm_clk_div {TYPE_2__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ scaled_div_max (struct bcm_clk_div*) ; 
 scalar_t__ scaled_div_min (struct bcm_clk_div*) ; 

__attribute__((used)) static inline u32
divider(struct bcm_clk_div *div, u64 scaled_div)
{
	BUG_ON(scaled_div < scaled_div_min(div));
	BUG_ON(scaled_div > scaled_div_max(div));

	return (u32)(scaled_div - ((u64)1 << div->u.s.frac_width));
}