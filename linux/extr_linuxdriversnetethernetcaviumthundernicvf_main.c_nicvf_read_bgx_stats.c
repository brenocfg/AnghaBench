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
struct TYPE_2__ {int /*<<< orphan*/ * tx_stats; int /*<<< orphan*/ * rx_stats; } ;
struct nicvf {TYPE_1__ bgx_stats; } ;
struct bgx_stats_msg {size_t idx; int /*<<< orphan*/  stats; scalar_t__ rx; } ;

/* Variables and functions */

__attribute__((used)) static void nicvf_read_bgx_stats(struct nicvf *nic, struct bgx_stats_msg *bgx)
{
	if (bgx->rx)
		nic->bgx_stats.rx_stats[bgx->idx] = bgx->stats;
	else
		nic->bgx_stats.tx_stats[bgx->idx] = bgx->stats;
}