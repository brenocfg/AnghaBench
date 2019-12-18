#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct pp_ctx {int /*<<< orphan*/  timer; int /*<<< orphan*/  in_db; TYPE_1__* ntb; int /*<<< orphan*/  count; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HRTIMER_MODE_REL ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  delay_ms ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hrtimer_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ms_to_ktime (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntb_db_clear (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntb_db_set_mask (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntb_msg_clear_sts (TYPE_1__*,int) ; 
 int ntb_msg_read (TYPE_1__*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntb_peer_port_number (TYPE_1__*,int) ; 
 int ntb_spad_read (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pp_pong(struct pp_ctx *pp)
{
	u32 msg_data = -1, spad_data = -1;
	int pidx = 0;

	/* Read pong data */
	spad_data = ntb_spad_read(pp->ntb, 0);
	msg_data = ntb_msg_read(pp->ntb, &pidx, 0);
	ntb_msg_clear_sts(pp->ntb, -1);

	/*
	 * Scratchpad and message data may differ, since message register can't
	 * be rewritten unless status is cleared. Additionally either of them
	 * might be unsupported
	 */
	dev_dbg(&pp->ntb->dev, "Pong spad %#x, msg %#x (port %d)\n",
		spad_data, msg_data, ntb_peer_port_number(pp->ntb, pidx));

	atomic_inc(&pp->count);

	ntb_db_set_mask(pp->ntb, pp->in_db);
	ntb_db_clear(pp->ntb, pp->in_db);

	hrtimer_start(&pp->timer, ms_to_ktime(delay_ms), HRTIMER_MODE_REL);
}