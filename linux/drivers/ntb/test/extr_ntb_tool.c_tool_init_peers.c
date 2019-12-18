#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tool_ctx {int peer_cnt; TYPE_2__* peers; TYPE_1__* ntb; } ;
struct TYPE_4__ {int pidx; struct tool_ctx* tc; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_2__* devm_kcalloc (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int ntb_peer_port_count (TYPE_1__*) ; 

__attribute__((used)) static int tool_init_peers(struct tool_ctx *tc)
{
	int pidx;

	tc->peer_cnt = ntb_peer_port_count(tc->ntb);
	tc->peers = devm_kcalloc(&tc->ntb->dev, tc->peer_cnt,
				 sizeof(*tc->peers), GFP_KERNEL);
	if (tc->peers == NULL)
		return -ENOMEM;

	for (pidx = 0; pidx < tc->peer_cnt; pidx++) {
		tc->peers[pidx].pidx = pidx;
		tc->peers[pidx].tc = tc;
	}

	return 0;
}