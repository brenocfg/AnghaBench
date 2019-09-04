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
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pxa25x_freqs ; 
 int pxa2xx_determine_rate (struct clk_rate_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int clk_pxa25x_cpll_determine_rate(struct clk_hw *hw,
					  struct clk_rate_request *req)
{
	return pxa2xx_determine_rate(req, pxa25x_freqs,
				     ARRAY_SIZE(pxa25x_freqs));
}