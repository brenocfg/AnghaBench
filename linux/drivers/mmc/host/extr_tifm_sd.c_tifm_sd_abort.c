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
struct tifm_sd {TYPE_3__* dev; int /*<<< orphan*/  cmd_flags; TYPE_2__* req; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {TYPE_1__* cmd; } ;
struct TYPE_4__ {int /*<<< orphan*/  opcode; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 struct tifm_sd* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct tifm_sd* host ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tifm_eject (TYPE_3__*) ; 
 int /*<<< orphan*/  timer ; 

__attribute__((used)) static void tifm_sd_abort(struct timer_list *t)
{
	struct tifm_sd *host = from_timer(host, t, timer);

	pr_err("%s : card failed to respond for a long period of time "
	       "(%x, %x)\n",
	       dev_name(&host->dev->dev), host->req->cmd->opcode, host->cmd_flags);

	tifm_eject(host->dev);
}