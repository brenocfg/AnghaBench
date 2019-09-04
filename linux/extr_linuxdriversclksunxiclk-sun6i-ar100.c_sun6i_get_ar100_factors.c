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
struct factors_request {int rate; int parent_rate; unsigned long m; int p; } ;

/* Variables and functions */
 unsigned long DIV_ROUND_UP (int,int) ; 

__attribute__((used)) static void sun6i_get_ar100_factors(struct factors_request *req)
{
	unsigned long div;
	int shift;

	/* clock only divides */
	if (req->rate > req->parent_rate)
		req->rate = req->parent_rate;

	div = DIV_ROUND_UP(req->parent_rate, req->rate);

	if (div < 32)
		shift = 0;
	else if (div >> 1 < 32)
		shift = 1;
	else if (div >> 2 < 32)
		shift = 2;
	else
		shift = 3;

	div >>= shift;

	if (div > 32)
		div = 32;

	req->rate = (req->parent_rate >> shift) / div;
	req->m = div - 1;
	req->p = shift;
}