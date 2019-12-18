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
struct host1x_syncpt {int /*<<< orphan*/  id; int /*<<< orphan*/  base_val; struct host1x* host; } ;
struct host1x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HOST1X_SYNC_SYNCPT_BASE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  host1x_sync_readl (struct host1x*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void syncpt_read_wait_base(struct host1x_syncpt *sp)
{
#if HOST1X_HW < 7
	struct host1x *host = sp->host;

	sp->base_val =
		host1x_sync_readl(host, HOST1X_SYNC_SYNCPT_BASE(sp->id));
#endif
}