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
struct vmw_stream {int /*<<< orphan*/  buf; } ;
struct vmw_private {struct vmw_overlay* overlay_priv; } ;
struct vmw_overlay {int /*<<< orphan*/  mutex; struct vmw_stream* stream; } ;

/* Variables and functions */
 int VMW_MAX_NUM_STREAMS ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int vmw_overlay_stop (struct vmw_private*,int,int,int) ; 

int vmw_overlay_stop_all(struct vmw_private *dev_priv)
{
	struct vmw_overlay *overlay = dev_priv->overlay_priv;
	int i, ret;

	if (!overlay)
		return 0;

	mutex_lock(&overlay->mutex);

	for (i = 0; i < VMW_MAX_NUM_STREAMS; i++) {
		struct vmw_stream *stream = &overlay->stream[i];
		if (!stream->buf)
			continue;

		ret = vmw_overlay_stop(dev_priv, i, false, false);
		WARN_ON(ret != 0);
	}

	mutex_unlock(&overlay->mutex);

	return 0;
}