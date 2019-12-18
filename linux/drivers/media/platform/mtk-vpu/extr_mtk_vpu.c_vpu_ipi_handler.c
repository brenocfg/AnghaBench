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
struct vpu_ipi_desc {int /*<<< orphan*/  priv; int /*<<< orphan*/  (* handler ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct share_obj {size_t id; int /*<<< orphan*/  len; int /*<<< orphan*/  share_buf; } ;
struct mtk_vpu {int* ipi_id_ack; int /*<<< orphan*/  dev; int /*<<< orphan*/  ack_wq; struct vpu_ipi_desc* ipi_desc; struct share_obj* recv_buf; } ;

/* Variables and functions */
 size_t IPI_MAX ; 
 size_t IPI_VPU_INIT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vpu_ipi_handler(struct mtk_vpu *vpu)
{
	struct share_obj *rcv_obj = vpu->recv_buf;
	struct vpu_ipi_desc *ipi_desc = vpu->ipi_desc;

	if (rcv_obj->id < IPI_MAX && ipi_desc[rcv_obj->id].handler) {
		ipi_desc[rcv_obj->id].handler(rcv_obj->share_buf,
					      rcv_obj->len,
					      ipi_desc[rcv_obj->id].priv);
		if (rcv_obj->id > IPI_VPU_INIT) {
			vpu->ipi_id_ack[rcv_obj->id] = true;
			wake_up(&vpu->ack_wq);
		}
	} else {
		dev_err(vpu->dev, "No such ipi id = %d\n", rcv_obj->id);
	}
}