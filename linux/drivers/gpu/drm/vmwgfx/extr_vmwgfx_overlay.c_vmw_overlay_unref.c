#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct vmw_private {struct vmw_overlay* overlay_priv; } ;
struct vmw_overlay {int /*<<< orphan*/  mutex; TYPE_1__* stream; } ;
struct TYPE_2__ {int claimed; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOSYS ; 
 size_t VMW_MAX_NUM_STREAMS ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmw_overlay_stop (struct vmw_private*,size_t,int,int) ; 

int vmw_overlay_unref(struct vmw_private *dev_priv, uint32_t stream_id)
{
	struct vmw_overlay *overlay = dev_priv->overlay_priv;

	BUG_ON(stream_id >= VMW_MAX_NUM_STREAMS);

	if (!overlay)
		return -ENOSYS;

	mutex_lock(&overlay->mutex);

	WARN_ON(!overlay->stream[stream_id].claimed);
	vmw_overlay_stop(dev_priv, stream_id, false, false);
	overlay->stream[stream_id].claimed = false;

	mutex_unlock(&overlay->mutex);
	return 0;
}