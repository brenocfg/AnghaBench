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
struct perf_peer {scalar_t__ outbuf_size; int /*<<< orphan*/  pidx; struct perf_ctx* perf; int /*<<< orphan*/  outbuf; } ;
struct perf_ctx {TYPE_1__* ntb; int /*<<< orphan*/  gidx; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  devm_ioremap_wc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ max_mw_size ; 
 int ntb_peer_mw_get_addr (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*) ; 

__attribute__((used)) static int perf_setup_peer_mw(struct perf_peer *peer)
{
	struct perf_ctx *perf = peer->perf;
	phys_addr_t phys_addr;
	int ret;

	/* Get outbound MW parameters and map it */
	ret = ntb_peer_mw_get_addr(perf->ntb, perf->gidx, &phys_addr,
				   &peer->outbuf_size);
	if (ret)
		return ret;

	peer->outbuf = devm_ioremap_wc(&perf->ntb->dev, phys_addr,
					peer->outbuf_size);
	if (!peer->outbuf)
		return -ENOMEM;

	if (max_mw_size && peer->outbuf_size > max_mw_size) {
		peer->outbuf_size = max_mw_size;
		dev_warn(&peer->perf->ntb->dev,
			"Peer %d outbuf reduced to %pa\n", peer->pidx,
			&peer->outbuf_size);
	}

	return 0;
}