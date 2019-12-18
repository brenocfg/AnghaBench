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
typedef  void* u32 ;
struct sk_buff {int /*<<< orphan*/  data; } ;
struct ehea_rwqe {TYPE_4__* sg_list; int /*<<< orphan*/  wr_id; } ;
struct ehea_qp_init_attr {int act_nr_rwqes_rq2; int act_nr_rwqes_rq3; } ;
struct ehea_qp {struct ehea_qp_init_attr init_attr; } ;
struct TYPE_7__ {void* lkey; } ;
struct TYPE_6__ {struct sk_buff** arr; } ;
struct TYPE_5__ {struct sk_buff** arr; } ;
struct ehea_port_res {TYPE_3__ recv_mr; TYPE_2__ rq3_skba; TYPE_1__ rq2_skba; } ;
struct TYPE_8__ {void* vaddr; void* l_key; } ;

/* Variables and functions */
 int EHEA_BMASK_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EHEA_WR_ID_INDEX ; 
 struct ehea_rwqe* ehea_get_next_rwqe (struct ehea_qp*,int) ; 
 void* ehea_map_vaddr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ehea_update_rqs(struct ehea_qp *orig_qp, struct ehea_port_res *pr)
{
	struct ehea_qp qp = *orig_qp;
	struct ehea_qp_init_attr *init_attr = &qp.init_attr;
	struct ehea_rwqe *rwqe;
	struct sk_buff **skba_rq2 = pr->rq2_skba.arr;
	struct sk_buff **skba_rq3 = pr->rq3_skba.arr;
	struct sk_buff *skb;
	u32 lkey = pr->recv_mr.lkey;


	int i;
	int index;

	for (i = 0; i < init_attr->act_nr_rwqes_rq2 + 1; i++) {
		rwqe = ehea_get_next_rwqe(&qp, 2);
		rwqe->sg_list[0].l_key = lkey;
		index = EHEA_BMASK_GET(EHEA_WR_ID_INDEX, rwqe->wr_id);
		skb = skba_rq2[index];
		if (skb)
			rwqe->sg_list[0].vaddr = ehea_map_vaddr(skb->data);
	}

	for (i = 0; i < init_attr->act_nr_rwqes_rq3 + 1; i++) {
		rwqe = ehea_get_next_rwqe(&qp, 3);
		rwqe->sg_list[0].l_key = lkey;
		index = EHEA_BMASK_GET(EHEA_WR_ID_INDEX, rwqe->wr_id);
		skb = skba_rq3[index];
		if (skb)
			rwqe->sg_list[0].vaddr = ehea_map_vaddr(skb->data);
	}
}