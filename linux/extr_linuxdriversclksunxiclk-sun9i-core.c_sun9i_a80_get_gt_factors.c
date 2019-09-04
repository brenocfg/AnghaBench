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
struct factors_request {int parent_rate; int rate; int m; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int) ; 

__attribute__((used)) static void sun9i_a80_get_gt_factors(struct factors_request *req)
{
	u32 div;

	if (req->parent_rate < req->rate)
		req->rate = req->parent_rate;

	div = DIV_ROUND_UP(req->parent_rate, req->rate);

	/* maximum divider is 4 */
	if (div > 4)
		div = 4;

	req->rate = req->parent_rate / div;
	req->m = div;
}