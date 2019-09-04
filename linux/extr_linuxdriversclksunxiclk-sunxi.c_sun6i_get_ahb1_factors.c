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
typedef  int u8 ;
struct factors_request {int parent_rate; int rate; scalar_t__ parent_index; int p; int m; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int) ; 
 scalar_t__ SUN6I_AHB1_PARENT_PLL6 ; 
 int __roundup_pow_of_two (int) ; 

__attribute__((used)) static void sun6i_get_ahb1_factors(struct factors_request *req)
{
	u8 div, calcp, calcm = 1;

	/*
	 * clock can only divide, so we will never be able to achieve
	 * frequencies higher than the parent frequency
	 */
	if (req->parent_rate && req->rate > req->parent_rate)
		req->rate = req->parent_rate;

	div = DIV_ROUND_UP(req->parent_rate, req->rate);

	/* calculate pre-divider if parent is pll6 */
	if (req->parent_index == SUN6I_AHB1_PARENT_PLL6) {
		if (div < 4)
			calcp = 0;
		else if (div / 2 < 4)
			calcp = 1;
		else if (div / 4 < 4)
			calcp = 2;
		else
			calcp = 3;

		calcm = DIV_ROUND_UP(div, 1 << calcp);
	} else {
		calcp = __roundup_pow_of_two(div);
		calcp = calcp > 3 ? 3 : calcp;
	}

	req->rate = (req->parent_rate / calcm) >> calcp;
	req->p = calcp;
	req->m = calcm - 1;
}