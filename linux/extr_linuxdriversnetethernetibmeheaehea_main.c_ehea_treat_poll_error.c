#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  len; int /*<<< orphan*/  arr; } ;
struct TYPE_7__ {int /*<<< orphan*/  len; int /*<<< orphan*/  arr; } ;
struct TYPE_6__ {int /*<<< orphan*/  err_frame_crc; int /*<<< orphan*/  err_ip_cksum; int /*<<< orphan*/  err_tcp_cksum; } ;
struct ehea_port_res {int /*<<< orphan*/  port; TYPE_5__* qp; TYPE_3__ rq3_skba; TYPE_2__ rq2_skba; TYPE_1__ p_stats; } ;
struct ehea_cqe {int status; } ;
struct TYPE_9__ {int /*<<< orphan*/  qp_nr; } ;
struct TYPE_10__ {TYPE_4__ init_attr; } ;

/* Variables and functions */
 int EHEA_CQE_STAT_ERR_CRC ; 
 int EHEA_CQE_STAT_ERR_IP ; 
 int EHEA_CQE_STAT_ERR_TCP ; 
 int EHEA_CQE_STAT_FAT_ERR_MASK ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  ehea_dump (struct ehea_cqe*,int,char*) ; 
 int /*<<< orphan*/  ehea_schedule_port_reset (int /*<<< orphan*/ ) ; 
 struct sk_buff* get_skb_by_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ehea_cqe*) ; 
 scalar_t__ netif_msg_rx_err (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ehea_treat_poll_error(struct ehea_port_res *pr, int rq,
				 struct ehea_cqe *cqe, int *processed_rq2,
				 int *processed_rq3)
{
	struct sk_buff *skb;

	if (cqe->status & EHEA_CQE_STAT_ERR_TCP)
		pr->p_stats.err_tcp_cksum++;
	if (cqe->status & EHEA_CQE_STAT_ERR_IP)
		pr->p_stats.err_ip_cksum++;
	if (cqe->status & EHEA_CQE_STAT_ERR_CRC)
		pr->p_stats.err_frame_crc++;

	if (rq == 2) {
		*processed_rq2 += 1;
		skb = get_skb_by_index(pr->rq2_skba.arr, pr->rq2_skba.len, cqe);
		dev_kfree_skb(skb);
	} else if (rq == 3) {
		*processed_rq3 += 1;
		skb = get_skb_by_index(pr->rq3_skba.arr, pr->rq3_skba.len, cqe);
		dev_kfree_skb(skb);
	}

	if (cqe->status & EHEA_CQE_STAT_FAT_ERR_MASK) {
		if (netif_msg_rx_err(pr->port)) {
			pr_err("Critical receive error for QP %d. Resetting port.\n",
			       pr->qp->init_attr.qp_nr);
			ehea_dump(cqe, sizeof(*cqe), "CQE");
		}
		ehea_schedule_port_reset(pr->port);
		return 1;
	}

	return 0;
}