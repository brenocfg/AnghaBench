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
struct red_stats {int /*<<< orphan*/  pdrop; int /*<<< orphan*/  forced_mark; } ;
struct nfp_alink_xstats {scalar_t__ pdrop; scalar_t__ ecn_marked; } ;

/* Variables and functions */

__attribute__((used)) static void
nfp_abm_stats_red_calculate(struct nfp_alink_xstats *new,
			    struct nfp_alink_xstats *old,
			    struct red_stats *stats)
{
	stats->forced_mark += new->ecn_marked - old->ecn_marked;
	stats->pdrop += new->pdrop - old->pdrop;
}