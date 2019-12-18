#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct pp_ctx {int /*<<< orphan*/  lock; int /*<<< orphan*/  in_db; TYPE_1__* ntb; int /*<<< orphan*/  out_db; int /*<<< orphan*/  out_pidx; int /*<<< orphan*/  count; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntb_db_clear_mask (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntb_peer_db_set (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntb_peer_msg_write (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntb_peer_port_number (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntb_peer_spad_write (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pp_ping(struct pp_ctx *pp)
{
	u32 count;

	count = atomic_read(&pp->count);

	spin_lock(&pp->lock);
	ntb_peer_spad_write(pp->ntb, pp->out_pidx, 0, count);
	ntb_peer_msg_write(pp->ntb, pp->out_pidx, 0, count);

	dev_dbg(&pp->ntb->dev, "Ping port %d spad %#x, msg %#x\n",
		ntb_peer_port_number(pp->ntb, pp->out_pidx), count, count);

	ntb_peer_db_set(pp->ntb, pp->out_db);
	ntb_db_clear_mask(pp->ntb, pp->in_db);
	spin_unlock(&pp->lock);
}