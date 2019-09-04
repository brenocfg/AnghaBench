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
typedef  unsigned long u32 ;
struct clk_rate_request {unsigned long best_parent_rate; struct clk_hw* best_parent_hw; scalar_t__ rate; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int abs (scalar_t__) ; 

__attribute__((used)) static void clk_generated_best_diff(struct clk_rate_request *req,
				    struct clk_hw *parent,
				    unsigned long parent_rate, u32 div,
				    int *best_diff, long *best_rate)
{
	unsigned long tmp_rate;
	int tmp_diff;

	if (!div)
		tmp_rate = parent_rate;
	else
		tmp_rate = parent_rate / div;
	tmp_diff = abs(req->rate - tmp_rate);

	if (*best_diff < 0 || *best_diff > tmp_diff) {
		*best_rate = tmp_rate;
		*best_diff = tmp_diff;
		req->best_parent_rate = parent_rate;
		req->best_parent_hw = parent;
	}
}