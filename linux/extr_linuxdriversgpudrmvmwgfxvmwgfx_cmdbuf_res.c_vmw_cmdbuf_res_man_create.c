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
struct vmw_cmdbuf_res_manager {int /*<<< orphan*/  resources; int /*<<< orphan*/  list; struct vmw_private* dev_priv; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct vmw_cmdbuf_res_manager* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VMW_CMDBUF_RES_MAN_HT_ORDER ; 
 int drm_ht_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct vmw_cmdbuf_res_manager*) ; 
 struct vmw_cmdbuf_res_manager* kzalloc (int,int /*<<< orphan*/ ) ; 

struct vmw_cmdbuf_res_manager *
vmw_cmdbuf_res_man_create(struct vmw_private *dev_priv)
{
	struct vmw_cmdbuf_res_manager *man;
	int ret;

	man = kzalloc(sizeof(*man), GFP_KERNEL);
	if (!man)
		return ERR_PTR(-ENOMEM);

	man->dev_priv = dev_priv;
	INIT_LIST_HEAD(&man->list);
	ret = drm_ht_create(&man->resources, VMW_CMDBUF_RES_MAN_HT_ORDER);
	if (ret == 0)
		return man;

	kfree(man);
	return ERR_PTR(ret);
}