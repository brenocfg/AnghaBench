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
struct vmw_private {scalar_t__ has_mob; } ;
struct vmw_ctx_validation_info {int dummy; } ;
typedef  enum vmw_res_type { ____Placeholder_vmw_res_type } vmw_res_type ;

/* Variables and functions */
 int vmw_res_context ; 
 int vmw_res_dx_context ; 

__attribute__((used)) static unsigned int vmw_execbuf_res_size(struct vmw_private *dev_priv,
					 enum vmw_res_type res_type)
{
	return (res_type == vmw_res_dx_context ||
		(res_type == vmw_res_context && dev_priv->has_mob)) ?
		sizeof(struct vmw_ctx_validation_info) : 0;
}