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
struct host1x_syncpt {int id; struct host1x* host; } ;
struct host1x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  HOST1X_SYNC_SYNCPT_CPU_INCR (int) ; 
 int /*<<< orphan*/  host1x_sync_writel (struct host1x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  host1x_syncpt_client_managed (struct host1x_syncpt*) ; 
 scalar_t__ host1x_syncpt_idle (struct host1x_syncpt*) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int syncpt_cpu_incr(struct host1x_syncpt *sp)
{
	struct host1x *host = sp->host;
	u32 reg_offset = sp->id / 32;

	if (!host1x_syncpt_client_managed(sp) &&
	    host1x_syncpt_idle(sp))
		return -EINVAL;

	host1x_sync_writel(host, BIT(sp->id % 32),
			   HOST1X_SYNC_SYNCPT_CPU_INCR(reg_offset));
	wmb();

	return 0;
}