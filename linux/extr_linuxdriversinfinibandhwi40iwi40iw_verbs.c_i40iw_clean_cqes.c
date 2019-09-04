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
struct TYPE_6__ {int /*<<< orphan*/  qp_uk; } ;
struct i40iw_qp {TYPE_3__ sc_qp; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* iw_cq_clean ) (int /*<<< orphan*/ *,struct i40iw_cq_uk*) ;} ;
struct i40iw_cq_uk {TYPE_2__ ops; } ;
struct TYPE_4__ {struct i40iw_cq_uk cq_uk; } ;
struct i40iw_cq {TYPE_1__ sc_cq; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,struct i40iw_cq_uk*) ; 

__attribute__((used)) static void i40iw_clean_cqes(struct i40iw_qp *iwqp, struct i40iw_cq *iwcq)
{
	struct i40iw_cq_uk *ukcq = &iwcq->sc_cq.cq_uk;

	ukcq->ops.iw_cq_clean(&iwqp->sc_qp.qp_uk, ukcq);
}