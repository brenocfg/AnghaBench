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
struct TYPE_2__ {int (* get_rate ) (struct v4l2_clk*) ;} ;

/* Variables and functions */
 int ENOSYS ; 
 unsigned long clk_get_rate (scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct v4l2_clk*) ; 
 int v4l2_clk_lock_driver (struct v4l2_clk*) ; 
 int /*<<< orphan*/  v4l2_clk_unlock_driver (struct v4l2_clk*) ; 

unsigned long v4l2_clk_get_rate(struct v4l2_clk *clk)
{
	int ret;

	if (clk->clk)
		return clk_get_rate(clk->clk);

	ret = v4l2_clk_lock_driver(clk);
	if (ret < 0)
		return ret;

	mutex_lock(&clk->lock);
	if (!clk->ops->get_rate)
		ret = -ENOSYS;
	else
		ret = clk->ops->get_rate(clk);
	mutex_unlock(&clk->lock);

	v4l2_clk_unlock_driver(clk);

	return ret;
}