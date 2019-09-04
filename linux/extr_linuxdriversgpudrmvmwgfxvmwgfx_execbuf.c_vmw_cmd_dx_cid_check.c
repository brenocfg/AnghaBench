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
struct vmw_sw_context {struct vmw_resource_val_node* dx_ctx_node; } ;
struct vmw_resource_val_node {int dummy; } ;
struct vmw_private {int dummy; } ;
typedef  int /*<<< orphan*/  SVGA3dCmdHeader ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vmw_cmd_dx_cid_check(struct vmw_private *dev_priv,
				struct vmw_sw_context *sw_context,
				SVGA3dCmdHeader *header)
{
	struct vmw_resource_val_node *ctx_node = sw_context->dx_ctx_node;

	if (unlikely(ctx_node == NULL)) {
		DRM_ERROR("DX Context not set.\n");
		return -EINVAL;
	}

	return 0;
}