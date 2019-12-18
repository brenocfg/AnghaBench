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
typedef  int /*<<< orphan*/  u32 ;
struct i40iw_sc_qp {scalar_t__ back_qp; } ;
struct TYPE_2__ {int /*<<< orphan*/  qp_num; } ;
struct i40iw_qp {int /*<<< orphan*/  iwpd; struct i40iw_device* iwdev; TYPE_1__ ibqp; } ;
struct i40iw_device {int dummy; } ;
struct i40iw_cqp_request {scalar_t__ param; } ;

/* Variables and functions */
 int /*<<< orphan*/  i40iw_free_qp_resources (struct i40iw_device*,struct i40iw_qp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40iw_rem_devusecount (struct i40iw_device*) ; 
 int /*<<< orphan*/  i40iw_rem_pdusecount (int /*<<< orphan*/ ,struct i40iw_device*) ; 

__attribute__((used)) static void i40iw_free_qp(struct i40iw_cqp_request *cqp_request, u32 num)
{
	struct i40iw_sc_qp *qp = (struct i40iw_sc_qp *)cqp_request->param;
	struct i40iw_qp *iwqp = (struct i40iw_qp *)qp->back_qp;
	struct i40iw_device *iwdev;
	u32 qp_num = iwqp->ibqp.qp_num;

	iwdev = iwqp->iwdev;

	i40iw_rem_pdusecount(iwqp->iwpd, iwdev);
	i40iw_free_qp_resources(iwdev, iwqp, qp_num);
	i40iw_rem_devusecount(iwdev);
}