#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct vfe_output {int state; int /*<<< orphan*/ ** buf; TYPE_4__* last_buffer; int /*<<< orphan*/  reg_update; scalar_t__ wait_reg_update; } ;
struct vfe_device {int /*<<< orphan*/  output_lock; TYPE_2__* line; TYPE_1__* ops; } ;
typedef  enum vfe_line_id { ____Placeholder_vfe_line_id } vfe_line_id ;
struct TYPE_7__ {int /*<<< orphan*/  vb2_buf; } ;
struct TYPE_8__ {TYPE_3__ vb; } ;
struct TYPE_6__ {struct vfe_output output; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* reg_update_clear ) (struct vfe_device*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  VB2_BUF_STATE_DONE ; 
#define  VFE_OUTPUT_CONTINUOUS 129 
 int VFE_OUTPUT_IDLE ; 
#define  VFE_OUTPUT_SINGLE 128 
 int VFE_OUTPUT_STOPPING ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct vfe_device*,int) ; 
 int /*<<< orphan*/  vb2_buffer_done (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* vfe_buf_get_pending (struct vfe_output*) ; 
 int /*<<< orphan*/  vfe_output_frame_drop (struct vfe_device*,struct vfe_output*,int) ; 
 int /*<<< orphan*/  vfe_output_init_addrs (struct vfe_device*,struct vfe_output*,int) ; 

__attribute__((used)) static void vfe_isr_reg_update(struct vfe_device *vfe, enum vfe_line_id line_id)
{
	struct vfe_output *output;
	unsigned long flags;

	spin_lock_irqsave(&vfe->output_lock, flags);
	vfe->ops->reg_update_clear(vfe, line_id);

	output = &vfe->line[line_id].output;

	if (output->wait_reg_update) {
		output->wait_reg_update = 0;
		complete(&output->reg_update);
		spin_unlock_irqrestore(&vfe->output_lock, flags);
		return;
	}

	if (output->state == VFE_OUTPUT_STOPPING) {
		/* Release last buffer when hw is idle */
		if (output->last_buffer) {
			vb2_buffer_done(&output->last_buffer->vb.vb2_buf,
					VB2_BUF_STATE_DONE);
			output->last_buffer = NULL;
		}
		output->state = VFE_OUTPUT_IDLE;

		/* Buffers received in stopping state are queued in */
		/* dma pending queue, start next capture here */

		output->buf[0] = vfe_buf_get_pending(output);
		output->buf[1] = vfe_buf_get_pending(output);

		if (!output->buf[0] && output->buf[1]) {
			output->buf[0] = output->buf[1];
			output->buf[1] = NULL;
		}

		if (output->buf[0])
			output->state = VFE_OUTPUT_SINGLE;

		if (output->buf[1])
			output->state = VFE_OUTPUT_CONTINUOUS;

		switch (output->state) {
		case VFE_OUTPUT_SINGLE:
			vfe_output_frame_drop(vfe, output, 2);
			break;
		case VFE_OUTPUT_CONTINUOUS:
			vfe_output_frame_drop(vfe, output, 3);
			break;
		default:
			vfe_output_frame_drop(vfe, output, 0);
			break;
		}

		vfe_output_init_addrs(vfe, output, 1);
	}

	spin_unlock_irqrestore(&vfe->output_lock, flags);
}