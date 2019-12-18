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
struct TYPE_4__ {void* addr_offset; void* data; } ;
struct ntb_transport_qp {int use_msi; TYPE_3__* ndev; TYPE_1__ peer_msi_desc; } ;
struct ntb_transport_ctx {unsigned int msi_spad_offset; int /*<<< orphan*/  ndev; int /*<<< orphan*/  use_msi; struct ntb_transport_qp* qp_vec; } ;
struct TYPE_6__ {TYPE_2__* pdev; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PIDX ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,unsigned int,void*,void*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,unsigned int) ; 
 void* ntb_peer_spad_read (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int ntb_spad_count (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ntb_transport_setup_qp_peer_msi(struct ntb_transport_ctx *nt,
					    unsigned int qp_num)
{
	struct ntb_transport_qp *qp = &nt->qp_vec[qp_num];
	int spad = qp_num * 2 + nt->msi_spad_offset;

	if (!nt->use_msi)
		return;

	if (spad >= ntb_spad_count(nt->ndev))
		return;

	qp->peer_msi_desc.addr_offset =
		ntb_peer_spad_read(qp->ndev, PIDX, spad);
	qp->peer_msi_desc.data =
		ntb_peer_spad_read(qp->ndev, PIDX, spad + 1);

	dev_dbg(&qp->ndev->pdev->dev, "QP%d Peer MSI addr=%x data=%x\n",
		qp_num, qp->peer_msi_desc.addr_offset, qp->peer_msi_desc.data);

	if (qp->peer_msi_desc.addr_offset) {
		qp->use_msi = true;
		dev_info(&qp->ndev->pdev->dev,
			 "Using MSI interrupts for QP%d\n", qp_num);
	}
}