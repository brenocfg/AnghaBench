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
struct vmw_private {struct vmw_overlay* overlay_priv; } ;
struct vmw_overlay {TYPE_1__* stream; } ;
struct TYPE_2__ {scalar_t__ buf; } ;

/* Variables and functions */
 int ENOSYS ; 
 int VMW_MAX_NUM_STREAMS ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  kfree (struct vmw_overlay*) ; 
 int /*<<< orphan*/  vmw_overlay_stop (struct vmw_private*,int,int,int) ; 

int vmw_overlay_close(struct vmw_private *dev_priv)
{
	struct vmw_overlay *overlay = dev_priv->overlay_priv;
	bool forgotten_buffer = false;
	int i;

	if (!overlay)
		return -ENOSYS;

	for (i = 0; i < VMW_MAX_NUM_STREAMS; i++) {
		if (overlay->stream[i].buf) {
			forgotten_buffer = true;
			vmw_overlay_stop(dev_priv, i, false, false);
		}
	}

	WARN_ON(forgotten_buffer);

	dev_priv->overlay_priv = NULL;
	kfree(overlay);

	return 0;
}