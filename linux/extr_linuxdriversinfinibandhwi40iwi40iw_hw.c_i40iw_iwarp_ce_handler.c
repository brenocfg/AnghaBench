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
struct i40iw_sc_cq {struct i40iw_cq* back_cq; } ;
struct i40iw_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  cq_context; int /*<<< orphan*/  (* comp_handler ) (TYPE_1__*,int /*<<< orphan*/ ) ;} ;
struct i40iw_cq {TYPE_1__ ibcq; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i40iw_iwarp_ce_handler(struct i40iw_device *iwdev,
				   struct i40iw_sc_cq *iwcq)
{
	struct i40iw_cq *i40iwcq = iwcq->back_cq;

	if (i40iwcq->ibcq.comp_handler)
		i40iwcq->ibcq.comp_handler(&i40iwcq->ibcq,
					   i40iwcq->ibcq.cq_context);
}