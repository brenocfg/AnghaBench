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
typedef  int u32 ;
struct factors_request {int parent_rate; int rate; int p; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_UP (int,int) ; 
 int order_base_2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sun5i_a13_get_ahb_factors(struct factors_request *req)
{
	u32 div;

	/* divide only */
	if (req->parent_rate < req->rate)
		req->rate = req->parent_rate;

	/*
	 * user manual says valid speed is 8k ~ 276M, but tests show it
	 * can work at speeds up to 300M, just after reparenting to pll6
	 */
	if (req->rate < 8000)
		req->rate = 8000;
	if (req->rate > 300000000)
		req->rate = 300000000;

	div = order_base_2(DIV_ROUND_UP(req->parent_rate, req->rate));

	/* p = 0 ~ 3 */
	if (div > 3)
		div = 3;

	req->rate = req->parent_rate >> div;

	req->p = div;
}