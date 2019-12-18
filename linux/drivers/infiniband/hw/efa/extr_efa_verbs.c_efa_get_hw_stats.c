#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct efa_com_basic_stats {void* rx_drops; void* rx_pkts; void* rx_bytes; void* tx_pkts; void* tx_bytes; } ;
union efa_com_get_stats_result {struct efa_com_basic_stats basic_stats; } ;
typedef  int /*<<< orphan*/  u8 ;
struct rdma_hw_stats {void** value; } ;
struct ib_device {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  create_ah_err; int /*<<< orphan*/  alloc_ucontext_err; int /*<<< orphan*/  reg_mr_err; int /*<<< orphan*/  create_qp_err; int /*<<< orphan*/  alloc_pd_err; } ;
struct efa_stats {TYPE_2__ sw_stats; int /*<<< orphan*/  keep_alive_rcvd; } ;
struct efa_com_stats_admin {int /*<<< orphan*/  no_completion; int /*<<< orphan*/  completed_cmd; int /*<<< orphan*/  submitted_cmd; } ;
struct TYPE_4__ {struct efa_com_stats_admin stats; } ;
struct TYPE_6__ {TYPE_1__ aq; } ;
struct efa_dev {struct efa_stats stats; TYPE_3__ edev; } ;
struct efa_com_get_stats_params {int /*<<< orphan*/  scope; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EFA_ADMIN_GET_STATS_SCOPE_ALL ; 
 int /*<<< orphan*/  EFA_ADMIN_GET_STATS_TYPE_BASIC ; 
 size_t EFA_ALLOC_PD_ERR ; 
 size_t EFA_ALLOC_UCONTEXT_ERR ; 
 size_t EFA_COMPLETED_CMDS ; 
 size_t EFA_CREATE_AH_ERR ; 
 size_t EFA_CREATE_QP_ERR ; 
 size_t EFA_KEEP_ALIVE_RCVD ; 
 size_t EFA_NO_COMPLETION_CMDS ; 
 size_t EFA_REG_MR_ERR ; 
 size_t EFA_RX_BYTES ; 
 size_t EFA_RX_DROPS ; 
 size_t EFA_RX_PKTS ; 
 size_t EFA_SUBMITTED_CMDS ; 
 size_t EFA_TX_BYTES ; 
 size_t EFA_TX_PKTS ; 
 void* atomic64_read (int /*<<< orphan*/ *) ; 
 int efa_com_get_stats (TYPE_3__*,struct efa_com_get_stats_params*,union efa_com_get_stats_result*) ; 
 int /*<<< orphan*/  efa_stats_names ; 
 struct efa_dev* to_edev (struct ib_device*) ; 

int efa_get_hw_stats(struct ib_device *ibdev, struct rdma_hw_stats *stats,
		     u8 port_num, int index)
{
	struct efa_com_get_stats_params params = {};
	union efa_com_get_stats_result result;
	struct efa_dev *dev = to_edev(ibdev);
	struct efa_com_basic_stats *bs;
	struct efa_com_stats_admin *as;
	struct efa_stats *s;
	int err;

	params.type = EFA_ADMIN_GET_STATS_TYPE_BASIC;
	params.scope = EFA_ADMIN_GET_STATS_SCOPE_ALL;

	err = efa_com_get_stats(&dev->edev, &params, &result);
	if (err)
		return err;

	bs = &result.basic_stats;
	stats->value[EFA_TX_BYTES] = bs->tx_bytes;
	stats->value[EFA_TX_PKTS] = bs->tx_pkts;
	stats->value[EFA_RX_BYTES] = bs->rx_bytes;
	stats->value[EFA_RX_PKTS] = bs->rx_pkts;
	stats->value[EFA_RX_DROPS] = bs->rx_drops;

	as = &dev->edev.aq.stats;
	stats->value[EFA_SUBMITTED_CMDS] = atomic64_read(&as->submitted_cmd);
	stats->value[EFA_COMPLETED_CMDS] = atomic64_read(&as->completed_cmd);
	stats->value[EFA_NO_COMPLETION_CMDS] = atomic64_read(&as->no_completion);

	s = &dev->stats;
	stats->value[EFA_KEEP_ALIVE_RCVD] = atomic64_read(&s->keep_alive_rcvd);
	stats->value[EFA_ALLOC_PD_ERR] = atomic64_read(&s->sw_stats.alloc_pd_err);
	stats->value[EFA_CREATE_QP_ERR] = atomic64_read(&s->sw_stats.create_qp_err);
	stats->value[EFA_REG_MR_ERR] = atomic64_read(&s->sw_stats.reg_mr_err);
	stats->value[EFA_ALLOC_UCONTEXT_ERR] = atomic64_read(&s->sw_stats.alloc_ucontext_err);
	stats->value[EFA_CREATE_AH_ERR] = atomic64_read(&s->sw_stats.create_ah_err);

	return ARRAY_SIZE(efa_stats_names);
}