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
typedef  int /*<<< orphan*/  ustats ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct qed_ptt {int dummy; } ;
struct qed_hwfn {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  rx_bcast_pkts; int /*<<< orphan*/  rx_mcast_pkts; int /*<<< orphan*/  rx_ucast_pkts; int /*<<< orphan*/  rx_bcast_bytes; int /*<<< orphan*/  rx_mcast_bytes; int /*<<< orphan*/  rx_ucast_bytes; } ;
struct qed_eth_stats {TYPE_1__ common; } ;
struct eth_ustorm_per_queue_stat {int /*<<< orphan*/  rcv_bcast_pkts; int /*<<< orphan*/  rcv_mcast_pkts; int /*<<< orphan*/  rcv_ucast_pkts; int /*<<< orphan*/  rcv_bcast_bytes; int /*<<< orphan*/  rcv_mcast_bytes; int /*<<< orphan*/  rcv_ucast_bytes; } ;

/* Variables and functions */
 scalar_t__ HILO_64_REGPAIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __qed_get_vport_ustats_addrlen (struct qed_hwfn*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct eth_ustorm_per_queue_stat*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qed_memcpy_from (struct qed_hwfn*,struct qed_ptt*,struct eth_ustorm_per_queue_stat*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __qed_get_vport_ustats(struct qed_hwfn *p_hwfn,
				   struct qed_ptt *p_ptt,
				   struct qed_eth_stats *p_stats,
				   u16 statistics_bin)
{
	struct eth_ustorm_per_queue_stat ustats;
	u32 ustats_addr = 0, ustats_len = 0;

	__qed_get_vport_ustats_addrlen(p_hwfn, &ustats_addr, &ustats_len,
				       statistics_bin);

	memset(&ustats, 0, sizeof(ustats));
	qed_memcpy_from(p_hwfn, p_ptt, &ustats, ustats_addr, ustats_len);

	p_stats->common.rx_ucast_bytes +=
	    HILO_64_REGPAIR(ustats.rcv_ucast_bytes);
	p_stats->common.rx_mcast_bytes +=
	    HILO_64_REGPAIR(ustats.rcv_mcast_bytes);
	p_stats->common.rx_bcast_bytes +=
	    HILO_64_REGPAIR(ustats.rcv_bcast_bytes);
	p_stats->common.rx_ucast_pkts += HILO_64_REGPAIR(ustats.rcv_ucast_pkts);
	p_stats->common.rx_mcast_pkts += HILO_64_REGPAIR(ustats.rcv_mcast_pkts);
	p_stats->common.rx_bcast_pkts += HILO_64_REGPAIR(ustats.rcv_bcast_pkts);
}