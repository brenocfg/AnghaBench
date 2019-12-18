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
struct vmw_view {int committed; int view_id; int /*<<< orphan*/  srf_head; int /*<<< orphan*/  cotable_head; int /*<<< orphan*/  cotable; int /*<<< orphan*/  srf; } ;
struct vmw_surface {int /*<<< orphan*/  view_list; } ;
struct vmw_resource {int id; struct vmw_private* dev_priv; } ;
struct vmw_private {int /*<<< orphan*/  binding_mutex; } ;
typedef  enum vmw_cmdbuf_res_state { ____Placeholder_vmw_cmdbuf_res_state } vmw_cmdbuf_res_state ;

/* Variables and functions */
 int VMW_CMDBUF_RES_ADD ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmw_cotable_add_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct vmw_surface* vmw_res_to_srf (int /*<<< orphan*/ ) ; 
 struct vmw_view* vmw_view (struct vmw_resource*) ; 

__attribute__((used)) static void vmw_view_commit_notify(struct vmw_resource *res,
				   enum vmw_cmdbuf_res_state state)
{
	struct vmw_view *view = vmw_view(res);
	struct vmw_private *dev_priv = res->dev_priv;

	mutex_lock(&dev_priv->binding_mutex);
	if (state == VMW_CMDBUF_RES_ADD) {
		struct vmw_surface *srf = vmw_res_to_srf(view->srf);

		list_add_tail(&view->srf_head, &srf->view_list);
		vmw_cotable_add_resource(view->cotable, &view->cotable_head);
		view->committed = true;
		res->id = view->view_id;

	} else {
		list_del_init(&view->cotable_head);
		list_del_init(&view->srf_head);
		view->committed = false;
		res->id = -1;
	}
	mutex_unlock(&dev_priv->binding_mutex);
}