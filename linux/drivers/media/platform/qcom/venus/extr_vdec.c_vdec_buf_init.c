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
struct venus_inst {int /*<<< orphan*/  buf_count; } ;
struct vb2_buffer {int /*<<< orphan*/  vb2_queue; } ;

/* Variables and functions */
 struct venus_inst* vb2_get_drv_priv (int /*<<< orphan*/ ) ; 
 int venus_helper_vb2_buf_init (struct vb2_buffer*) ; 

__attribute__((used)) static int vdec_buf_init(struct vb2_buffer *vb)
{
	struct venus_inst *inst = vb2_get_drv_priv(vb->vb2_queue);

	inst->buf_count++;

	return venus_helper_vb2_buf_init(vb);
}