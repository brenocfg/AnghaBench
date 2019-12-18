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
struct vmw_private {int dummy; } ;
struct vmw_ctx_binding_state {struct vmw_private* dev_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ttm_mem_global_free (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vfree (struct vmw_ctx_binding_state*) ; 
 int /*<<< orphan*/  vmw_mem_glob (struct vmw_private*) ; 

void vmw_binding_state_free(struct vmw_ctx_binding_state *cbs)
{
	struct vmw_private *dev_priv = cbs->dev_priv;

	vfree(cbs);
	ttm_mem_global_free(vmw_mem_glob(dev_priv), sizeof(*cbs));
}