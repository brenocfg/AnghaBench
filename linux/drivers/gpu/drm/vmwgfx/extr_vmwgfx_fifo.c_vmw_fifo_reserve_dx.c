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
struct vmw_private {scalar_t__ cman; } ;

/* Variables and functions */
 scalar_t__ IS_ERR_OR_NULL (void*) ; 
 int SVGA3D_INVALID_ID ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 void* vmw_cmdbuf_reserve (scalar_t__,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 void* vmw_local_fifo_reserve (struct vmw_private*,int /*<<< orphan*/ ) ; 

void *vmw_fifo_reserve_dx(struct vmw_private *dev_priv, uint32_t bytes,
			  int ctx_id)
{
	void *ret;

	if (dev_priv->cman)
		ret = vmw_cmdbuf_reserve(dev_priv->cman, bytes,
					 ctx_id, false, NULL);
	else if (ctx_id == SVGA3D_INVALID_ID)
		ret = vmw_local_fifo_reserve(dev_priv, bytes);
	else {
		WARN(1, "Command buffer has not been allocated.\n");
		ret = NULL;
	}
	if (IS_ERR_OR_NULL(ret))
		return NULL;

	return ret;
}