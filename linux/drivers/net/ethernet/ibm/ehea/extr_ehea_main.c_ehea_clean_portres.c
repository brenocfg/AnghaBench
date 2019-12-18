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
struct TYPE_8__ {int len; int /*<<< orphan*/ * arr; } ;
struct TYPE_7__ {int len; int /*<<< orphan*/ * arr; } ;
struct TYPE_6__ {int len; int /*<<< orphan*/ * arr; } ;
struct TYPE_5__ {int len; int /*<<< orphan*/ * arr; } ;
struct ehea_port_res {TYPE_4__ sq_skba; TYPE_3__ rq3_skba; TYPE_2__ rq2_skba; TYPE_1__ rq1_skba; int /*<<< orphan*/  eq; int /*<<< orphan*/  recv_cq; int /*<<< orphan*/  send_cq; scalar_t__ qp; int /*<<< orphan*/  napi; } ;
struct ehea_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ehea_destroy_cq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ehea_destroy_eq (int /*<<< orphan*/ ) ; 
 int ehea_destroy_qp (scalar_t__) ; 
 int ehea_rem_smrs (struct ehea_port_res*) ; 
 int /*<<< orphan*/  netif_napi_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ehea_clean_portres(struct ehea_port *port, struct ehea_port_res *pr)
{
	int ret, i;

	if (pr->qp)
		netif_napi_del(&pr->napi);

	ret = ehea_destroy_qp(pr->qp);

	if (!ret) {
		ehea_destroy_cq(pr->send_cq);
		ehea_destroy_cq(pr->recv_cq);
		ehea_destroy_eq(pr->eq);

		for (i = 0; i < pr->rq1_skba.len; i++)
			dev_kfree_skb(pr->rq1_skba.arr[i]);

		for (i = 0; i < pr->rq2_skba.len; i++)
			dev_kfree_skb(pr->rq2_skba.arr[i]);

		for (i = 0; i < pr->rq3_skba.len; i++)
			dev_kfree_skb(pr->rq3_skba.arr[i]);

		for (i = 0; i < pr->sq_skba.len; i++)
			dev_kfree_skb(pr->sq_skba.arr[i]);

		vfree(pr->rq1_skba.arr);
		vfree(pr->rq2_skba.arr);
		vfree(pr->rq3_skba.arr);
		vfree(pr->sq_skba.arr);
		ret = ehea_rem_smrs(pr);
	}
	return ret;
}