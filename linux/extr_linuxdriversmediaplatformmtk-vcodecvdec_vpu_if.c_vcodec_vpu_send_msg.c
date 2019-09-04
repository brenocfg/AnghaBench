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
typedef  int /*<<< orphan*/  uint32_t ;
struct vdec_vpu_inst {int failure; int /*<<< orphan*/  id; int /*<<< orphan*/  dev; scalar_t__ signaled; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtk_vcodec_debug (struct vdec_vpu_inst*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_vcodec_err (struct vdec_vpu_inst*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int vpu_ipi_send (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 

__attribute__((used)) static int vcodec_vpu_send_msg(struct vdec_vpu_inst *vpu, void *msg, int len)
{
	int err;

	mtk_vcodec_debug(vpu, "id=%X", *(uint32_t *)msg);

	vpu->failure = 0;
	vpu->signaled = 0;

	err = vpu_ipi_send(vpu->dev, vpu->id, msg, len);
	if (err) {
		mtk_vcodec_err(vpu, "send fail vpu_id=%d msg_id=%X status=%d",
			       vpu->id, *(uint32_t *)msg, err);
		return err;
	}

	return vpu->failure;
}