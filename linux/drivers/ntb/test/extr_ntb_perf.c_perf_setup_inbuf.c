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
struct perf_peer {scalar_t__ inbuf_size; int /*<<< orphan*/  inbuf_xlat; int /*<<< orphan*/  gidx; int /*<<< orphan*/  pidx; int /*<<< orphan*/  inbuf; struct perf_ctx* perf; } ;
struct perf_ctx {TYPE_1__* ntb; int /*<<< orphan*/  gidx; } ;
typedef  scalar_t__ resource_size_t ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_ALIGNED (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  PERF_CMD_SXLAT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ntb_mw_get_align (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 int ntb_mw_set_trans (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  perf_cmd_exec (struct perf_peer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_free_inbuf (struct perf_peer*) ; 
 scalar_t__ round_up (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int perf_setup_inbuf(struct perf_peer *peer)
{
	resource_size_t xlat_align, size_align, size_max;
	struct perf_ctx *perf = peer->perf;
	int ret;

	/* Get inbound MW parameters */
	ret = ntb_mw_get_align(perf->ntb, peer->pidx, perf->gidx,
			       &xlat_align, &size_align, &size_max);
	if (ret) {
		dev_err(&perf->ntb->dev, "Couldn't get inbuf restrictions\n");
		return ret;
	}

	if (peer->inbuf_size > size_max) {
		dev_err(&perf->ntb->dev, "Too big inbuf size %pa > %pa\n",
			&peer->inbuf_size, &size_max);
		return -EINVAL;
	}

	peer->inbuf_size = round_up(peer->inbuf_size, size_align);

	perf_free_inbuf(peer);

	peer->inbuf = dma_alloc_coherent(&perf->ntb->dev, peer->inbuf_size,
					 &peer->inbuf_xlat, GFP_KERNEL);
	if (!peer->inbuf) {
		dev_err(&perf->ntb->dev, "Failed to alloc inbuf of %pa\n",
			&peer->inbuf_size);
		return -ENOMEM;
	}
	if (!IS_ALIGNED(peer->inbuf_xlat, xlat_align)) {
		dev_err(&perf->ntb->dev, "Unaligned inbuf allocated\n");
		goto err_free_inbuf;
	}

	ret = ntb_mw_set_trans(perf->ntb, peer->pidx, peer->gidx,
			       peer->inbuf_xlat, peer->inbuf_size);
	if (ret) {
		dev_err(&perf->ntb->dev, "Failed to set inbuf translation\n");
		goto err_free_inbuf;
	}

	/*
	 * We submit inbuf xlat transmission cmd for execution here to follow
	 * the code architecture, even though this method is called from service
	 * work itself so the command will be executed right after it returns.
	 */
	(void)perf_cmd_exec(peer, PERF_CMD_SXLAT);

	return 0;

err_free_inbuf:
	perf_free_inbuf(peer);

	return ret;
}