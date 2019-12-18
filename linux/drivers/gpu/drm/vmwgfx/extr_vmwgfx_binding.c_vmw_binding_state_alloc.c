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
struct vmw_ctx_binding_state {int /*<<< orphan*/  list; struct vmw_private* dev_priv; } ;
struct ttm_operation_ctx {int interruptible; int no_wait_gpu; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct vmw_ctx_binding_state* ERR_PTR (int) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int ttm_mem_global_alloc (int /*<<< orphan*/ ,int,struct ttm_operation_ctx*) ; 
 int /*<<< orphan*/  ttm_mem_global_free (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vmw_mem_glob (struct vmw_private*) ; 
 struct vmw_ctx_binding_state* vzalloc (int) ; 

struct vmw_ctx_binding_state *
vmw_binding_state_alloc(struct vmw_private *dev_priv)
{
	struct vmw_ctx_binding_state *cbs;
	struct ttm_operation_ctx ctx = {
		.interruptible = false,
		.no_wait_gpu = false
	};
	int ret;

	ret = ttm_mem_global_alloc(vmw_mem_glob(dev_priv), sizeof(*cbs),
				&ctx);
	if (ret)
		return ERR_PTR(ret);

	cbs = vzalloc(sizeof(*cbs));
	if (!cbs) {
		ttm_mem_global_free(vmw_mem_glob(dev_priv), sizeof(*cbs));
		return ERR_PTR(-ENOMEM);
	}

	cbs->dev_priv = dev_priv;
	INIT_LIST_HEAD(&cbs->list);

	return cbs;
}