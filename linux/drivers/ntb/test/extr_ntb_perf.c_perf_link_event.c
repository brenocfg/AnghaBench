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
struct perf_peer {int /*<<< orphan*/  sts; } ;
struct perf_ctx {int pcnt; struct perf_peer* peers; } ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_CMD_CLEAR ; 
 int /*<<< orphan*/  PERF_CMD_SSIZE ; 
 int /*<<< orphan*/  PERF_STS_LNKUP ; 
 int /*<<< orphan*/  perf_cmd_exec (struct perf_peer*,int /*<<< orphan*/ ) ; 
 int perf_link_is_up (struct perf_peer*) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void perf_link_event(void *ctx)
{
	struct perf_ctx *perf = ctx;
	struct perf_peer *peer;
	bool lnk_up;
	int pidx;

	for (pidx = 0; pidx < perf->pcnt; pidx++) {
		peer = &perf->peers[pidx];

		lnk_up = perf_link_is_up(peer);

		if (lnk_up &&
		    !test_and_set_bit(PERF_STS_LNKUP, &peer->sts)) {
			perf_cmd_exec(peer, PERF_CMD_SSIZE);
		} else if (!lnk_up &&
			   test_and_clear_bit(PERF_STS_LNKUP, &peer->sts)) {
			perf_cmd_exec(peer, PERF_CMD_CLEAR);
		}
	}
}