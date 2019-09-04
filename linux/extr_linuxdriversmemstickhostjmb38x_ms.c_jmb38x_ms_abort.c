#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct timer_list {int dummy; } ;
struct memstick_host {int dummy; } ;
struct jmb38x_ms_host {int /*<<< orphan*/  lock; TYPE_1__* req; TYPE_3__* chip; struct memstick_host* msh; } ;
struct TYPE_6__ {TYPE_2__* pdev; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  error; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETIME ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 struct jmb38x_ms_host* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct jmb38x_ms_host* host ; 
 int /*<<< orphan*/  jmb38x_ms_complete_cmd (struct memstick_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  timer ; 

__attribute__((used)) static void jmb38x_ms_abort(struct timer_list *t)
{
	struct jmb38x_ms_host *host = from_timer(host, t, timer);
	struct memstick_host *msh = host->msh;
	unsigned long flags;

	dev_dbg(&host->chip->pdev->dev, "abort\n");
	spin_lock_irqsave(&host->lock, flags);
	if (host->req) {
		host->req->error = -ETIME;
		jmb38x_ms_complete_cmd(msh, 0);
	}
	spin_unlock_irqrestore(&host->lock, flags);
}