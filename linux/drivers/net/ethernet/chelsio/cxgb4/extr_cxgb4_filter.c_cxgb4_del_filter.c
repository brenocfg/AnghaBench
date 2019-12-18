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
struct net_device {int dummy; } ;
struct filter_ctx {int result; int /*<<< orphan*/  completion; } ;
struct ch_filter_specification {int dummy; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int CXGB4_SHUTTING_DOWN ; 
 int ETIMEDOUT ; 
 int HZ ; 
 int __cxgb4_del_filter (struct net_device*,int,struct ch_filter_specification*,struct filter_ctx*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 TYPE_1__* netdev2adap (struct net_device*) ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,int) ; 

int cxgb4_del_filter(struct net_device *dev, int filter_id,
		     struct ch_filter_specification *fs)
{
	struct filter_ctx ctx;
	int ret;

	if (netdev2adap(dev)->flags & CXGB4_SHUTTING_DOWN)
		return 0;

	init_completion(&ctx.completion);

	ret = __cxgb4_del_filter(dev, filter_id, fs, &ctx);
	if (ret)
		goto out;

	/* Wait for reply */
	ret = wait_for_completion_timeout(&ctx.completion, 10 * HZ);
	if (!ret)
		return -ETIMEDOUT;

	ret = ctx.result;
out:
	return ret;
}