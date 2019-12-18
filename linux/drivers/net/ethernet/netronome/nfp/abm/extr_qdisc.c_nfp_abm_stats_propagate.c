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
struct nfp_alink_stats {scalar_t__ drops; scalar_t__ overlimits; scalar_t__ backlog_bytes; scalar_t__ backlog_pkts; scalar_t__ tx_bytes; scalar_t__ tx_pkts; } ;

/* Variables and functions */

__attribute__((used)) static void
nfp_abm_stats_propagate(struct nfp_alink_stats *parent,
			struct nfp_alink_stats *child)
{
	parent->tx_pkts		+= child->tx_pkts;
	parent->tx_bytes	+= child->tx_bytes;
	parent->backlog_pkts	+= child->backlog_pkts;
	parent->backlog_bytes	+= child->backlog_bytes;
	parent->overlimits	+= child->overlimits;
	parent->drops		+= child->drops;
}