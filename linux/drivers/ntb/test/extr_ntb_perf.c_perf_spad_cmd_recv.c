#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  scalar_t__ u32 ;
struct perf_peer {int /*<<< orphan*/  gidx; } ;
struct perf_ctx {int pcnt; TYPE_1__* ntb; struct perf_peer* peers; int /*<<< orphan*/  gidx; } ;
typedef  enum perf_cmd { ____Placeholder_perf_cmd } perf_cmd ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODATA ; 
 scalar_t__ PERF_CMD_INVAL ; 
 int /*<<< orphan*/  PERF_SPAD_CMD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PERF_SPAD_HDATA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PERF_SPAD_LDATA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PERF_SPAD_NOTIFY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  ntb_db_clear (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ntb_spad_read (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntb_spad_write (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  perf_link_is_up (struct perf_peer*) ; 

__attribute__((used)) static int perf_spad_cmd_recv(struct perf_ctx *perf, int *pidx,
			      enum perf_cmd *cmd, u64 *data)
{
	struct perf_peer *peer;
	u32 val;

	ntb_db_clear(perf->ntb, PERF_SPAD_NOTIFY(perf->gidx));

	/*
	 * We start scanning all over, since cleared DB may have been set
	 * by any peer. Yes, it makes peer with smaller index being
	 * serviced with greater priority, but it's convenient for spad
	 * and message code unification and simplicity.
	 */
	for (*pidx = 0; *pidx < perf->pcnt; (*pidx)++) {
		peer = &perf->peers[*pidx];

		if (!perf_link_is_up(peer))
			continue;

		val = ntb_spad_read(perf->ntb, PERF_SPAD_CMD(peer->gidx));
		if (val == PERF_CMD_INVAL)
			continue;

		*cmd = val;

		val = ntb_spad_read(perf->ntb, PERF_SPAD_LDATA(peer->gidx));
		*data = val;

		val = ntb_spad_read(perf->ntb, PERF_SPAD_HDATA(peer->gidx));
		*data |= (u64)val << 32;

		/* Next command can be retrieved from now */
		ntb_spad_write(perf->ntb, PERF_SPAD_CMD(peer->gidx),
			       PERF_CMD_INVAL);

		dev_dbg(&perf->ntb->dev, "CMD recv: %d 0x%llx\n", *cmd, *data);

		return 0;
	}

	return -ENODATA;
}