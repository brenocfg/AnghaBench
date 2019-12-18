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
struct notifier_block {int dummy; } ;
struct clk_wzrd {scalar_t__ clk_in1; int speed_grade; scalar_t__ axi_clk; scalar_t__ suspended; } ;
struct clk_notifier_data {scalar_t__ clk; unsigned long new_rate; } ;

/* Variables and functions */
#define  ABORT_RATE_CHANGE 130 
 int NOTIFY_BAD ; 
 int NOTIFY_DONE ; 
 int NOTIFY_OK ; 
#define  POST_RATE_CHANGE 129 
#define  PRE_RATE_CHANGE 128 
 unsigned long WZRD_ACLK_MAX_FREQ ; 
 unsigned long* clk_wzrd_max_freq ; 
 struct clk_wzrd* to_clk_wzrd (struct notifier_block*) ; 

__attribute__((used)) static int clk_wzrd_clk_notifier(struct notifier_block *nb, unsigned long event,
				 void *data)
{
	unsigned long max;
	struct clk_notifier_data *ndata = data;
	struct clk_wzrd *clk_wzrd = to_clk_wzrd(nb);

	if (clk_wzrd->suspended)
		return NOTIFY_OK;

	if (ndata->clk == clk_wzrd->clk_in1)
		max = clk_wzrd_max_freq[clk_wzrd->speed_grade - 1];
	else if (ndata->clk == clk_wzrd->axi_clk)
		max = WZRD_ACLK_MAX_FREQ;
	else
		return NOTIFY_DONE;	/* should never happen */

	switch (event) {
	case PRE_RATE_CHANGE:
		if (ndata->new_rate > max)
			return NOTIFY_BAD;
		return NOTIFY_OK;
	case POST_RATE_CHANGE:
	case ABORT_RATE_CHANGE:
	default:
		return NOTIFY_DONE;
	}
}