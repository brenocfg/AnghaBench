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
struct clk_rate_request {int rate; int best_parent_rate; } ;
struct clk_mmc {scalar_t__ id; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ HI3620_MMC_CIUCLK1 ; 
 struct clk_mmc* to_mmc (struct clk_hw*) ; 

__attribute__((used)) static int mmc_clk_determine_rate(struct clk_hw *hw,
				  struct clk_rate_request *req)
{
	struct clk_mmc *mclk = to_mmc(hw);

	if ((req->rate <= 13000000) && (mclk->id == HI3620_MMC_CIUCLK1)) {
		req->rate = 13000000;
		req->best_parent_rate = 26000000;
	} else if (req->rate <= 26000000) {
		req->rate = 25000000;
		req->best_parent_rate = 180000000;
	} else if (req->rate <= 52000000) {
		req->rate = 50000000;
		req->best_parent_rate = 360000000;
	} else if (req->rate <= 100000000) {
		req->rate = 100000000;
		req->best_parent_rate = 720000000;
	} else {
		/* max is 180M */
		req->rate = 180000000;
		req->best_parent_rate = 1440000000;
	}
	return -EINVAL;
}