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
typedef  int u16 ;
struct TYPE_4__ {int num_cons; int num_vf_cons; int /*<<< orphan*/  num_arfs_filters; } ;
struct qed_pf_params {TYPE_1__ eth_pf_params; } ;
struct qed_dev {int dummy; } ;
struct TYPE_6__ {TYPE_2__* common; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* update_pf_params ) (struct qed_dev*,struct qed_pf_params*) ;} ;

/* Variables and functions */
 int MAX_SB_PER_PF_MIMD ; 
 int /*<<< orphan*/  QEDE_RFS_MAX_FLTR ; 
 int QED_MIN_L2_CONS ; 
 int /*<<< orphan*/  memset (struct qed_pf_params*,int /*<<< orphan*/ ,int) ; 
 TYPE_3__* qed_ops ; 
 int /*<<< orphan*/  stub1 (struct qed_dev*,struct qed_pf_params*) ; 

__attribute__((used)) static void qede_update_pf_params(struct qed_dev *cdev)
{
	struct qed_pf_params pf_params;
	u16 num_cons;

	/* 64 rx + 64 tx + 64 XDP */
	memset(&pf_params, 0, sizeof(struct qed_pf_params));

	/* 1 rx + 1 xdp + max tx cos */
	num_cons = QED_MIN_L2_CONS;

	pf_params.eth_pf_params.num_cons = (MAX_SB_PER_PF_MIMD - 1) * num_cons;

	/* Same for VFs - make sure they'll have sufficient connections
	 * to support XDP Tx queues.
	 */
	pf_params.eth_pf_params.num_vf_cons = 48;

	pf_params.eth_pf_params.num_arfs_filters = QEDE_RFS_MAX_FLTR;
	qed_ops->common->update_pf_params(cdev, &pf_params);
}