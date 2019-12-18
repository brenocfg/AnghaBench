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
struct pp_ctx {TYPE_1__* ntb; int /*<<< orphan*/  in_db; int /*<<< orphan*/  timer; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  hrtimer_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ntb_db_set_mask (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pp_clear(struct pp_ctx *pp)
{
	hrtimer_cancel(&pp->timer);

	ntb_db_set_mask(pp->ntb, pp->in_db);

	dev_dbg(&pp->ntb->dev, "Ping-pong cancelled\n");
}