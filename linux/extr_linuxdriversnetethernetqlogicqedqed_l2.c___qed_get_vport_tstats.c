#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
typedef  int /*<<< orphan*/  tstats ;
struct tstorm_per_port_stat {int /*<<< orphan*/  eth_gft_drop_pkt; int /*<<< orphan*/  eth_mac_filter_discard; int /*<<< orphan*/  mftag_filter_discard; } ;
struct TYPE_5__ {int address; int len; } ;
struct TYPE_6__ {TYPE_1__ tstats; } ;
struct TYPE_7__ {TYPE_2__ stats_info; } ;
struct pfvf_acquire_resp_tlv {TYPE_3__ pfdev_info; } ;
struct qed_vf_iov {struct pfvf_acquire_resp_tlv acquire_resp; } ;
struct qed_ptt {int dummy; } ;
struct qed_hwfn {struct qed_vf_iov* vf_iov_info; int /*<<< orphan*/  cdev; } ;
struct TYPE_8__ {int /*<<< orphan*/  gft_filter_drop; int /*<<< orphan*/  mac_filter_discards; int /*<<< orphan*/  mftag_filter_discards; } ;
struct qed_eth_stats {TYPE_4__ common; } ;

/* Variables and functions */
 int BAR0_MAP_REG_TSDM_RAM ; 
 scalar_t__ HILO_64_REGPAIR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_PF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MFW_PORT (struct qed_hwfn*) ; 
 int TSTORM_PORT_STAT_OFFSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct tstorm_per_port_stat*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qed_memcpy_from (struct qed_hwfn*,struct qed_ptt*,struct tstorm_per_port_stat*,int,int) ; 

__attribute__((used)) static void __qed_get_vport_tstats(struct qed_hwfn *p_hwfn,
				   struct qed_ptt *p_ptt,
				   struct qed_eth_stats *p_stats,
				   u16 statistics_bin)
{
	struct tstorm_per_port_stat tstats;
	u32 tstats_addr, tstats_len;

	if (IS_PF(p_hwfn->cdev)) {
		tstats_addr = BAR0_MAP_REG_TSDM_RAM +
		    TSTORM_PORT_STAT_OFFSET(MFW_PORT(p_hwfn));
		tstats_len = sizeof(struct tstorm_per_port_stat);
	} else {
		struct qed_vf_iov *p_iov = p_hwfn->vf_iov_info;
		struct pfvf_acquire_resp_tlv *p_resp = &p_iov->acquire_resp;

		tstats_addr = p_resp->pfdev_info.stats_info.tstats.address;
		tstats_len = p_resp->pfdev_info.stats_info.tstats.len;
	}

	memset(&tstats, 0, sizeof(tstats));
	qed_memcpy_from(p_hwfn, p_ptt, &tstats, tstats_addr, tstats_len);

	p_stats->common.mftag_filter_discards +=
	    HILO_64_REGPAIR(tstats.mftag_filter_discard);
	p_stats->common.mac_filter_discards +=
	    HILO_64_REGPAIR(tstats.eth_mac_filter_discard);
	p_stats->common.gft_filter_drop +=
		HILO_64_REGPAIR(tstats.eth_gft_drop_pkt);
}