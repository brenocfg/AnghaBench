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
struct gve_rx_ring {int dummy; } ;
struct TYPE_4__ {TYPE_1__* dev; } ;
struct gve_notify_block {TYPE_2__ napi; struct gve_rx_ring* rx; } ;
typedef  int /*<<< orphan*/  netdev_features_t ;
struct TYPE_3__ {int /*<<< orphan*/  features; } ;

/* Variables and functions */
 int INT_MAX ; 
 int gve_clean_rx_done (struct gve_rx_ring*,int,int /*<<< orphan*/ ) ; 
 int gve_rx_work_pending (struct gve_rx_ring*) ; 

bool gve_rx_poll(struct gve_notify_block *block, int budget)
{
	struct gve_rx_ring *rx = block->rx;
	netdev_features_t feat;
	bool repoll = false;

	feat = block->napi.dev->features;

	/* If budget is 0, do all the work */
	if (budget == 0)
		budget = INT_MAX;

	if (budget > 0)
		repoll |= gve_clean_rx_done(rx, budget, feat);
	else
		repoll |= gve_rx_work_pending(rx);
	return repoll;
}