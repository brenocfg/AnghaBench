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
typedef  size_t uint32_t ;
struct vmw_stream {int paused; int /*<<< orphan*/  buf; } ;
struct vmw_private {struct vmw_overlay* overlay_priv; } ;
struct vmw_overlay {struct vmw_stream* stream; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  vmw_bo_unreference (int /*<<< orphan*/ *) ; 
 int vmw_overlay_move_buffer (struct vmw_private*,int /*<<< orphan*/ ,int,int) ; 
 int vmw_overlay_send_stop (struct vmw_private*,size_t,int) ; 

__attribute__((used)) static int vmw_overlay_stop(struct vmw_private *dev_priv,
			    uint32_t stream_id, bool pause,
			    bool interruptible)
{
	struct vmw_overlay *overlay = dev_priv->overlay_priv;
	struct vmw_stream *stream = &overlay->stream[stream_id];
	int ret;

	/* no buffer attached the stream is completely stopped */
	if (!stream->buf)
		return 0;

	/* If the stream is paused this is already done */
	if (!stream->paused) {
		ret = vmw_overlay_send_stop(dev_priv, stream_id,
					    interruptible);
		if (ret)
			return ret;

		/* We just remove the NO_EVICT flag so no -ENOMEM */
		ret = vmw_overlay_move_buffer(dev_priv, stream->buf, false,
					      interruptible);
		if (interruptible && ret == -ERESTARTSYS)
			return ret;
		else
			BUG_ON(ret != 0);
	}

	if (!pause) {
		vmw_bo_unreference(&stream->buf);
		stream->paused = false;
	} else {
		stream->paused = true;
	}

	return 0;
}