#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
struct vfe_output {scalar_t__ active_buf; scalar_t__ state; unsigned int wm_num; struct camss_buffer* last_buffer; int /*<<< orphan*/ * wm_idx; struct camss_buffer** buf; int /*<<< orphan*/  sequence; } ;
struct vfe_device {size_t* wm_output_map; int /*<<< orphan*/  output_lock; TYPE_3__* ops; TYPE_2__* camss; TYPE_1__* line; } ;
struct TYPE_10__ {int /*<<< orphan*/  timestamp; } ;
struct TYPE_9__ {TYPE_5__ vb2_buf; scalar_t__ sequence; } ;
struct camss_buffer {TYPE_4__ vb; int /*<<< orphan*/ * addr; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_8__ {scalar_t__ (* wm_get_ping_pong_status ) (struct vfe_device*,size_t) ;int /*<<< orphan*/  (* wm_set_pong_addr ) (struct vfe_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* wm_set_ping_addr ) (struct vfe_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {struct vfe_output output; } ;

/* Variables and functions */
 int /*<<< orphan*/  VB2_BUF_STATE_DONE ; 
 size_t VFE_LINE_NONE ; 
 scalar_t__ VFE_OUTPUT_STOPPING ; 
 int /*<<< orphan*/  dev_err_ratelimited (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ktime_get_ns () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ stub1 (struct vfe_device*,size_t) ; 
 int /*<<< orphan*/  stub2 (struct vfe_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct vfe_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vb2_buffer_done (TYPE_5__*,int /*<<< orphan*/ ) ; 
 struct camss_buffer* vfe_buf_get_pending (struct vfe_output*) ; 
 int /*<<< orphan*/  vfe_buf_update_wm_on_last (struct vfe_device*,struct vfe_output*) ; 
 int /*<<< orphan*/  vfe_buf_update_wm_on_next (struct vfe_device*,struct vfe_output*) ; 

__attribute__((used)) static void vfe_isr_wm_done(struct vfe_device *vfe, u8 wm)
{
	struct camss_buffer *ready_buf;
	struct vfe_output *output;
	dma_addr_t *new_addr;
	unsigned long flags;
	u32 active_index;
	u64 ts = ktime_get_ns();
	unsigned int i;

	active_index = vfe->ops->wm_get_ping_pong_status(vfe, wm);

	spin_lock_irqsave(&vfe->output_lock, flags);

	if (vfe->wm_output_map[wm] == VFE_LINE_NONE) {
		dev_err_ratelimited(vfe->camss->dev,
				    "Received wm done for unmapped index\n");
		goto out_unlock;
	}
	output = &vfe->line[vfe->wm_output_map[wm]].output;

	if (output->active_buf == active_index) {
		dev_err_ratelimited(vfe->camss->dev,
				    "Active buffer mismatch!\n");
		goto out_unlock;
	}
	output->active_buf = active_index;

	ready_buf = output->buf[!active_index];
	if (!ready_buf) {
		dev_err_ratelimited(vfe->camss->dev,
				    "Missing ready buf %d %d!\n",
				    !active_index, output->state);
		goto out_unlock;
	}

	ready_buf->vb.vb2_buf.timestamp = ts;
	ready_buf->vb.sequence = output->sequence++;

	/* Get next buffer */
	output->buf[!active_index] = vfe_buf_get_pending(output);
	if (!output->buf[!active_index]) {
		/* No next buffer - set same address */
		new_addr = ready_buf->addr;
		vfe_buf_update_wm_on_last(vfe, output);
	} else {
		new_addr = output->buf[!active_index]->addr;
		vfe_buf_update_wm_on_next(vfe, output);
	}

	if (active_index)
		for (i = 0; i < output->wm_num; i++)
			vfe->ops->wm_set_ping_addr(vfe, output->wm_idx[i],
						   new_addr[i]);
	else
		for (i = 0; i < output->wm_num; i++)
			vfe->ops->wm_set_pong_addr(vfe, output->wm_idx[i],
						   new_addr[i]);

	spin_unlock_irqrestore(&vfe->output_lock, flags);

	if (output->state == VFE_OUTPUT_STOPPING)
		output->last_buffer = ready_buf;
	else
		vb2_buffer_done(&ready_buf->vb.vb2_buf, VB2_BUF_STATE_DONE);

	return;

out_unlock:
	spin_unlock_irqrestore(&vfe->output_lock, flags);
}