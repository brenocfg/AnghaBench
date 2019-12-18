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
struct v4l2_clk {int enable; int /*<<< orphan*/  lock; TYPE_1__* ops; scalar_t__ clk; } ;
struct TYPE_2__ {int (* enable ) (struct v4l2_clk*) ;} ;

/* Variables and functions */
 int clk_prepare_enable (scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct v4l2_clk*) ; 
 int v4l2_clk_lock_driver (struct v4l2_clk*) ; 

int v4l2_clk_enable(struct v4l2_clk *clk)
{
	int ret;

	if (clk->clk)
		return clk_prepare_enable(clk->clk);

	ret = v4l2_clk_lock_driver(clk);
	if (ret < 0)
		return ret;

	mutex_lock(&clk->lock);

	if (++clk->enable == 1 && clk->ops->enable) {
		ret = clk->ops->enable(clk);
		if (ret < 0)
			clk->enable--;
	}

	mutex_unlock(&clk->lock);

	return ret;
}