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
typedef  size_t u16 ;
struct sk_buff {int dummy; } ;
struct hinic_rq_wqe {int dummy; } ;
struct hinic_rq {int /*<<< orphan*/  wq; struct sk_buff** saved_skb; } ;
struct hinic_hw_wqe {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hinic_cpu_to_be32 (struct hinic_rq_wqe*,int) ; 
 int /*<<< orphan*/  hinic_write_wqe (int /*<<< orphan*/ ,struct hinic_hw_wqe*,int) ; 

void hinic_rq_write_wqe(struct hinic_rq *rq, u16 prod_idx,
			struct hinic_rq_wqe *rq_wqe, struct sk_buff *skb)
{
	struct hinic_hw_wqe *hw_wqe = (struct hinic_hw_wqe *)rq_wqe;

	rq->saved_skb[prod_idx] = skb;

	/* The data in the HW should be in Big Endian Format */
	hinic_cpu_to_be32(rq_wqe, sizeof(*rq_wqe));

	hinic_write_wqe(rq->wq, hw_wqe, sizeof(*rq_wqe));
}