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
struct clk_rate_request {int dummy; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLK_MUX_ROUND_CLOSEST ; 
 int clk_mux_determine_rate_flags (struct clk_hw*,struct clk_rate_request*,int /*<<< orphan*/ ) ; 

int __clk_mux_determine_rate_closest(struct clk_hw *hw,
				     struct clk_rate_request *req)
{
	return clk_mux_determine_rate_flags(hw, req, CLK_MUX_ROUND_CLOSEST);
}