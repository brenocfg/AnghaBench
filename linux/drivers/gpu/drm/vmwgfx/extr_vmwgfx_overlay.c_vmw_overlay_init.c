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
struct vmw_overlay {TYPE_1__* stream; int /*<<< orphan*/  mutex; } ;
struct TYPE_2__ {int paused; int claimed; int /*<<< orphan*/ * buf; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int VMW_MAX_NUM_STREAMS ; 
 struct vmw_overlay* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

int vmw_overlay_init(struct vmw_private *dev_priv)
{
	struct vmw_overlay *overlay;
	int i;

	if (dev_priv->overlay_priv)
		return -EINVAL;

	overlay = kzalloc(sizeof(*overlay), GFP_KERNEL);
	if (!overlay)
		return -ENOMEM;

	mutex_init(&overlay->mutex);
	for (i = 0; i < VMW_MAX_NUM_STREAMS; i++) {
		overlay->stream[i].buf = NULL;
		overlay->stream[i].paused = false;
		overlay->stream[i].claimed = false;
	}

	dev_priv->overlay_priv = overlay;

	return 0;
}