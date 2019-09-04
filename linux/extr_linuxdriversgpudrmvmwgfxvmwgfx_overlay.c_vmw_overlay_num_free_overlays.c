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
struct vmw_overlay {int /*<<< orphan*/  mutex; TYPE_1__* stream; } ;
struct TYPE_2__ {int /*<<< orphan*/  claimed; } ;

/* Variables and functions */
 int VMW_MAX_NUM_STREAMS ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmw_overlay_available (struct vmw_private*) ; 

int vmw_overlay_num_free_overlays(struct vmw_private *dev_priv)
{
	struct vmw_overlay *overlay = dev_priv->overlay_priv;
	int i, k;

	if (!vmw_overlay_available(dev_priv))
		return 0;

	mutex_lock(&overlay->mutex);

	for (i = 0, k = 0; i < VMW_MAX_NUM_STREAMS; i++)
		if (!overlay->stream[i].claimed)
			k++;

	mutex_unlock(&overlay->mutex);

	return k;
}