#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct perf_peer {int pidx; int gidx; int /*<<< orphan*/  service; struct perf_ctx* perf; } ;
struct perf_ctx {int gidx; int pcnt; TYPE_1__* ntb; struct perf_peer* peers; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int ntb_peer_port_number (TYPE_1__*,int) ; 
 int ntb_port_number (TYPE_1__*) ; 
 int /*<<< orphan*/  perf_service_work ; 
 int perf_setup_peer_mw (struct perf_peer*) ; 

__attribute__((used)) static int perf_init_peers(struct perf_ctx *perf)
{
	struct perf_peer *peer;
	int pidx, lport, ret;

	lport = ntb_port_number(perf->ntb);
	perf->gidx = -1;
	for (pidx = 0; pidx < perf->pcnt; pidx++) {
		peer = &perf->peers[pidx];

		peer->perf = perf;
		peer->pidx = pidx;
		if (lport < ntb_peer_port_number(perf->ntb, pidx)) {
			if (perf->gidx == -1)
				perf->gidx = pidx;
			peer->gidx = pidx + 1;
		} else {
			peer->gidx = pidx;
		}
		INIT_WORK(&peer->service, perf_service_work);
	}
	if (perf->gidx == -1)
		perf->gidx = pidx;

	for (pidx = 0; pidx < perf->pcnt; pidx++) {
		ret = perf_setup_peer_mw(&perf->peers[pidx]);
		if (ret)
			return ret;
	}

	dev_dbg(&perf->ntb->dev, "Global port index %d\n", perf->gidx);

	return 0;
}