#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rxe_pkt_info {TYPE_1__* wqe; TYPE_2__* qp; } ;
struct rxe_av {int dummy; } ;
struct TYPE_4__ {struct rxe_av pri_av; } ;
struct TYPE_3__ {struct rxe_av av; } ;

/* Variables and functions */
 scalar_t__ IB_QPT_RC ; 
 scalar_t__ IB_QPT_UC ; 
 scalar_t__ qp_type (TYPE_2__*) ; 

struct rxe_av *rxe_get_av(struct rxe_pkt_info *pkt)
{
	if (!pkt || !pkt->qp)
		return NULL;

	if (qp_type(pkt->qp) == IB_QPT_RC || qp_type(pkt->qp) == IB_QPT_UC)
		return &pkt->qp->pri_av;

	return (pkt->wqe) ? &pkt->wqe->av : NULL;
}