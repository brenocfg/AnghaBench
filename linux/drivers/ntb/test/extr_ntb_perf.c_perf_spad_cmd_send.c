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
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
struct perf_peer {int /*<<< orphan*/  gidx; int /*<<< orphan*/  pidx; struct perf_ctx* perf; } ;
struct perf_ctx {TYPE_1__* ntb; int /*<<< orphan*/  gidx; } ;
typedef  enum perf_cmd { ____Placeholder_perf_cmd } perf_cmd ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ENOLINK ; 
 int MSG_TRIES ; 
 int /*<<< orphan*/  MSG_UDELAY_HIGH ; 
 int /*<<< orphan*/  MSG_UDELAY_LOW ; 
 scalar_t__ PERF_CMD_INVAL ; 
 int /*<<< orphan*/  PERF_SPAD_CMD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PERF_SPAD_HDATA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PERF_SPAD_LDATA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PERF_SPAD_NOTIFY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,...) ; 
 int lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntb_peer_db_set (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ntb_peer_spad_read (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntb_peer_spad_write (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  perf_link_is_up (struct perf_peer*) ; 
 int upper_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int perf_spad_cmd_send(struct perf_peer *peer, enum perf_cmd cmd,
			      u64 data)
{
	struct perf_ctx *perf = peer->perf;
	int try;
	u32 sts;

	dev_dbg(&perf->ntb->dev, "CMD send: %d 0x%llx\n", cmd, data);

	/*
	 * Perform predefined number of attempts before give up.
	 * We are sending the data to the port specific scratchpad, so
	 * to prevent a multi-port access race-condition. Additionally
	 * there is no need in local locking since only thread-safe
	 * service work is using this method.
	 */
	for (try = 0; try < MSG_TRIES; try++) {
		if (!perf_link_is_up(peer))
			return -ENOLINK;

		sts = ntb_peer_spad_read(perf->ntb, peer->pidx,
					 PERF_SPAD_CMD(perf->gidx));
		if (sts != PERF_CMD_INVAL) {
			usleep_range(MSG_UDELAY_LOW, MSG_UDELAY_HIGH);
			continue;
		}

		ntb_peer_spad_write(perf->ntb, peer->pidx,
				    PERF_SPAD_LDATA(perf->gidx),
				    lower_32_bits(data));
		ntb_peer_spad_write(perf->ntb, peer->pidx,
				    PERF_SPAD_HDATA(perf->gidx),
				    upper_32_bits(data));
		ntb_peer_spad_write(perf->ntb, peer->pidx,
				    PERF_SPAD_CMD(perf->gidx),
				    cmd);
		ntb_peer_db_set(perf->ntb, PERF_SPAD_NOTIFY(peer->gidx));

		dev_dbg(&perf->ntb->dev, "DB ring peer %#llx\n",
			PERF_SPAD_NOTIFY(peer->gidx));

		break;
	}

	return try < MSG_TRIES ? 0 : -EAGAIN;
}