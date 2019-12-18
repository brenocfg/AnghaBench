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
struct venc_vpu_ipi_msg_enc {int /*<<< orphan*/  is_key_frm; int /*<<< orphan*/  bs_size; int /*<<< orphan*/  state; } ;
struct venc_vpu_inst {int /*<<< orphan*/  is_key_frm; int /*<<< orphan*/  bs_size; int /*<<< orphan*/  state; } ;

/* Variables and functions */

__attribute__((used)) static void handle_enc_encode_msg(struct venc_vpu_inst *vpu, void *data)
{
	struct venc_vpu_ipi_msg_enc *msg = data;

	vpu->state = msg->state;
	vpu->bs_size = msg->bs_size;
	vpu->is_key_frm = msg->is_key_frm;
}