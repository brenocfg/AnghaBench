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
struct clk {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct clk*) ; 
 int PTR_ERR (struct clk*) ; 
 struct clk* clk_get_parent (struct clk*) ; 
 int clk_prepare_enable (struct clk*) ; 

__attribute__((used)) static int bcm2835_mark_sdc_parent_critical(struct clk *sdc)
{
	struct clk *parent = clk_get_parent(sdc);

	if (IS_ERR(parent))
		return PTR_ERR(parent);

	return clk_prepare_enable(parent);
}