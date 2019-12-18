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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  u32 ;
struct vmw_fifo_state {int capabilities; int /*<<< orphan*/  marker_queue; } ;
struct vmw_private {int /*<<< orphan*/  marker_seq; struct vmw_fifo_state fifo; } ;
struct svga_fifo_cmd_fence {int fence; } ;

/* Variables and functions */
 int ENOMEM ; 
 int HZ ; 
 int /*<<< orphan*/  SVGA_CMD_FENCE ; 
 int SVGA_FIFO_CAP_FENCE ; 
 int /*<<< orphan*/ * VMW_FIFO_RESERVE (struct vmw_private*,int) ; 
 int atomic_add_return (int,int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmw_fallback_wait (struct vmw_private*,int,int,int,int,int) ; 
 int /*<<< orphan*/  vmw_fifo_commit (struct vmw_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmw_fifo_commit_flush (struct vmw_private*,int) ; 
 int /*<<< orphan*/  vmw_marker_push (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vmw_update_seqno (struct vmw_private*,struct vmw_fifo_state*) ; 

int vmw_fifo_send_fence(struct vmw_private *dev_priv, uint32_t *seqno)
{
	struct vmw_fifo_state *fifo_state = &dev_priv->fifo;
	struct svga_fifo_cmd_fence *cmd_fence;
	u32 *fm;
	int ret = 0;
	uint32_t bytes = sizeof(u32) + sizeof(*cmd_fence);

	fm = VMW_FIFO_RESERVE(dev_priv, bytes);
	if (unlikely(fm == NULL)) {
		*seqno = atomic_read(&dev_priv->marker_seq);
		ret = -ENOMEM;
		(void)vmw_fallback_wait(dev_priv, false, true, *seqno,
					false, 3*HZ);
		goto out_err;
	}

	do {
		*seqno = atomic_add_return(1, &dev_priv->marker_seq);
	} while (*seqno == 0);

	if (!(fifo_state->capabilities & SVGA_FIFO_CAP_FENCE)) {

		/*
		 * Don't request hardware to send a fence. The
		 * waiting code in vmwgfx_irq.c will emulate this.
		 */

		vmw_fifo_commit(dev_priv, 0);
		return 0;
	}

	*fm++ = SVGA_CMD_FENCE;
	cmd_fence = (struct svga_fifo_cmd_fence *) fm;
	cmd_fence->fence = *seqno;
	vmw_fifo_commit_flush(dev_priv, bytes);
	(void) vmw_marker_push(&fifo_state->marker_queue, *seqno);
	vmw_update_seqno(dev_priv, fifo_state);

out_err:
	return ret;
}