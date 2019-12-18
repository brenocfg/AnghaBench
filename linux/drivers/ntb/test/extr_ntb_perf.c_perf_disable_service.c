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
typedef  int /*<<< orphan*/  u64 ;
struct perf_peer {int /*<<< orphan*/  gidx; int /*<<< orphan*/  service; } ;
struct perf_ctx {scalar_t__ cmd_send; int pcnt; int /*<<< orphan*/  ntb; int /*<<< orphan*/  gidx; struct perf_peer* peers; } ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_CMD_CLEAR ; 
 int /*<<< orphan*/  PERF_SPAD_CMD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PERF_SPAD_NOTIFY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ntb_clear_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntb_db_clear (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntb_db_set_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntb_link_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntb_msg_inbits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntb_msg_set_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntb_spad_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_cmd_exec (struct perf_peer*,int /*<<< orphan*/ ) ; 
 scalar_t__ perf_msg_cmd_send ; 

__attribute__((used)) static void perf_disable_service(struct perf_ctx *perf)
{
	int pidx;

	if (perf->cmd_send == perf_msg_cmd_send) {
		u64 inbits;

		inbits = ntb_msg_inbits(perf->ntb);
		(void)ntb_msg_set_mask(perf->ntb, inbits);
	} else {
		(void)ntb_db_set_mask(perf->ntb, PERF_SPAD_NOTIFY(perf->gidx));
	}

	ntb_clear_ctx(perf->ntb);

	for (pidx = 0; pidx < perf->pcnt; pidx++)
		perf_cmd_exec(&perf->peers[pidx], PERF_CMD_CLEAR);

	for (pidx = 0; pidx < perf->pcnt; pidx++)
		flush_work(&perf->peers[pidx].service);

	for (pidx = 0; pidx < perf->pcnt; pidx++) {
		struct perf_peer *peer = &perf->peers[pidx];

		ntb_spad_write(perf->ntb, PERF_SPAD_CMD(peer->gidx), 0);
	}

	ntb_db_clear(perf->ntb, PERF_SPAD_NOTIFY(perf->gidx));

	ntb_link_disable(perf->ntb);
}