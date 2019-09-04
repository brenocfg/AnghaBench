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
struct factors_request {int parent_rate; int rate; int m; int p; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int) ; 

__attribute__((used)) static void sun4i_get_apb1_factors(struct factors_request *req)
{
	u8 calcm, calcp;
	int div;

	if (req->parent_rate < req->rate)
		req->rate = req->parent_rate;

	div = DIV_ROUND_UP(req->parent_rate, req->rate);

	/* Invalid rate! */
	if (div > 32)
		return;

	if (div <= 4)
		calcp = 0;
	else if (div <= 8)
		calcp = 1;
	else if (div <= 16)
		calcp = 2;
	else
		calcp = 3;

	calcm = (div >> calcp) - 1;

	req->rate = (req->parent_rate >> calcp) / (calcm + 1);
	req->m = calcm;
	req->p = calcp;
}