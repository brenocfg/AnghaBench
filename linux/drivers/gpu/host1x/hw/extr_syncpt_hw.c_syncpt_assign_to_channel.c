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
struct host1x_syncpt {int /*<<< orphan*/  id; struct host1x* host; } ;
struct host1x_channel {int id; } ;
struct host1x {int /*<<< orphan*/  hv_regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  HOST1X_SYNC_SYNCPT_CH_APP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HOST1X_SYNC_SYNCPT_CH_APP_CH (int) ; 
 int /*<<< orphan*/  host1x_sync_writel (struct host1x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void syncpt_assign_to_channel(struct host1x_syncpt *sp,
				  struct host1x_channel *ch)
{
#if HOST1X_HW >= 6
	struct host1x *host = sp->host;

	if (!host->hv_regs)
		return;

	host1x_sync_writel(host,
			   HOST1X_SYNC_SYNCPT_CH_APP_CH(ch ? ch->id : 0xff),
			   HOST1X_SYNC_SYNCPT_CH_APP(sp->id));
#endif
}