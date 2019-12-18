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
struct nfp_abm_link {scalar_t__ root_qdisc; int /*<<< orphan*/  last_stats_update; } ;

/* Variables and functions */
 int /*<<< orphan*/  nfp_abm_stats_update_mq (struct nfp_abm_link*,scalar_t__) ; 

__attribute__((used)) static void __nfp_abm_stats_update(struct nfp_abm_link *alink, u64 time_now)
{
	alink->last_stats_update = time_now;
	if (alink->root_qdisc)
		nfp_abm_stats_update_mq(alink, alink->root_qdisc);
}