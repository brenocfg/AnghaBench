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
struct vmw_cmdbuf_res_manager {int /*<<< orphan*/  resources; } ;
struct vmw_cmdbuf_res {int /*<<< orphan*/  res; int /*<<< orphan*/  hash; int /*<<< orphan*/  head; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_ht_remove_item (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct vmw_cmdbuf_res*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmw_resource_unreference (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vmw_cmdbuf_res_free(struct vmw_cmdbuf_res_manager *man,
				struct vmw_cmdbuf_res *entry)
{
	list_del(&entry->head);
	WARN_ON(drm_ht_remove_item(&man->resources, &entry->hash));
	vmw_resource_unreference(&entry->res);
	kfree(entry);
}