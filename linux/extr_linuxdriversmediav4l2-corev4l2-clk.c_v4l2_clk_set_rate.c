#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct v4l2_clk {int /*<<< orphan*/  lock; TYPE_1__* ops; scalar_t__ clk; } ;
struct TYPE_2__ {int (* set_rate ) (struct v4l2_clk*,unsigned long) ;} ;

/* Variables and functions */
 int ENOSYS ; 
 long clk_round_rate (scalar_t__,unsigned long) ; 
 int clk_set_rate (scalar_t__,long) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct v4l2_clk*,unsigned long) ; 
 int v4l2_clk_lock_driver (struct v4l2_clk*) ; 
 int /*<<< orphan*/  v4l2_clk_unlock_driver (struct v4l2_clk*) ; 

int v4l2_clk_set_rate(struct v4l2_clk *clk, unsigned long rate)
{
	int ret;

	if (clk->clk) {
		long r = clk_round_rate(clk->clk, rate);
		if (r < 0)
			return r;
		return clk_set_rate(clk->clk, r);
	}

	ret = v4l2_clk_lock_driver(clk);

	if (ret < 0)
		return ret;

	mutex_lock(&clk->lock);
	if (!clk->ops->set_rate)
		ret = -ENOSYS;
	else
		ret = clk->ops->set_rate(clk, rate);
	mutex_unlock(&clk->lock);

	v4l2_clk_unlock_driver(clk);

	return ret;
}