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
struct amdgpu_fpriv {int /*<<< orphan*/  bo_list_lock; int /*<<< orphan*/  bo_list_handles; } ;
struct amdgpu_bo_list {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_bo_list_free ; 
 struct amdgpu_bo_list* idr_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void amdgpu_bo_list_destroy(struct amdgpu_fpriv *fpriv, int id)
{
	struct amdgpu_bo_list *list;

	mutex_lock(&fpriv->bo_list_lock);
	list = idr_remove(&fpriv->bo_list_handles, id);
	mutex_unlock(&fpriv->bo_list_lock);
	if (list)
		kref_put(&list->refcount, amdgpu_bo_list_free);
}