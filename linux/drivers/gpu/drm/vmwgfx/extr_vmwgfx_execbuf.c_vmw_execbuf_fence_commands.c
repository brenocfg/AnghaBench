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
typedef  int /*<<< orphan*/  uint32_t ;
struct vmw_private {int /*<<< orphan*/  fman; } ;
struct vmw_fence_obj {int dummy; } ;
struct drm_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  VMW_DEBUG_USER (char*) ; 
 int /*<<< orphan*/  VMW_FENCE_WAIT_TIMEOUT ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vmw_fallback_wait (struct vmw_private*,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int vmw_fence_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vmw_fence_obj**) ; 
 int vmw_fifo_send_fence (struct vmw_private*,int /*<<< orphan*/ *) ; 
 int vmw_user_fence_create (struct drm_file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vmw_fence_obj**,int /*<<< orphan*/ *) ; 

int vmw_execbuf_fence_commands(struct drm_file *file_priv,
			       struct vmw_private *dev_priv,
			       struct vmw_fence_obj **p_fence,
			       uint32_t *p_handle)
{
	uint32_t sequence;
	int ret;
	bool synced = false;

	/* p_handle implies file_priv. */
	BUG_ON(p_handle != NULL && file_priv == NULL);

	ret = vmw_fifo_send_fence(dev_priv, &sequence);
	if (unlikely(ret != 0)) {
		VMW_DEBUG_USER("Fence submission error. Syncing.\n");
		synced = true;
	}

	if (p_handle != NULL)
		ret = vmw_user_fence_create(file_priv, dev_priv->fman,
					    sequence, p_fence, p_handle);
	else
		ret = vmw_fence_create(dev_priv->fman, sequence, p_fence);

	if (unlikely(ret != 0 && !synced)) {
		(void) vmw_fallback_wait(dev_priv, false, false, sequence,
					 false, VMW_FENCE_WAIT_TIMEOUT);
		*p_fence = NULL;
	}

	return ret;
}