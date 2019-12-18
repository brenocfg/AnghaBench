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
typedef  int /*<<< orphan*/  u16 ;
struct qed_ptt {int dummy; } ;
struct qed_hwfn {scalar_t__ mcp_info; } ;
struct qed_eth_stats {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __qed_get_vport_mstats (struct qed_hwfn*,struct qed_ptt*,struct qed_eth_stats*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __qed_get_vport_port_stats (struct qed_hwfn*,struct qed_ptt*,struct qed_eth_stats*) ; 
 int /*<<< orphan*/  __qed_get_vport_pstats (struct qed_hwfn*,struct qed_ptt*,struct qed_eth_stats*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __qed_get_vport_tstats (struct qed_hwfn*,struct qed_ptt*,struct qed_eth_stats*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __qed_get_vport_ustats (struct qed_hwfn*,struct qed_ptt*,struct qed_eth_stats*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __qed_get_vport_stats(struct qed_hwfn *p_hwfn,
				  struct qed_ptt *p_ptt,
				  struct qed_eth_stats *stats,
				  u16 statistics_bin, bool b_get_port_stats)
{
	__qed_get_vport_mstats(p_hwfn, p_ptt, stats, statistics_bin);
	__qed_get_vport_ustats(p_hwfn, p_ptt, stats, statistics_bin);
	__qed_get_vport_tstats(p_hwfn, p_ptt, stats, statistics_bin);
	__qed_get_vport_pstats(p_hwfn, p_ptt, stats, statistics_bin);

	if (b_get_port_stats && p_hwfn->mcp_info)
		__qed_get_vport_port_stats(p_hwfn, p_ptt, stats);
}