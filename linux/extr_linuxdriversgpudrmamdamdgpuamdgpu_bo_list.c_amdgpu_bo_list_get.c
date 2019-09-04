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
struct amdgpu_fpriv {int /*<<< orphan*/  bo_list_handles; } ;
struct amdgpu_bo_list {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int ENOENT ; 
 struct amdgpu_bo_list* idr_find (int /*<<< orphan*/ *,int) ; 
 scalar_t__ kref_get_unless_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

int amdgpu_bo_list_get(struct amdgpu_fpriv *fpriv, int id,
		       struct amdgpu_bo_list **result)
{
	rcu_read_lock();
	*result = idr_find(&fpriv->bo_list_handles, id);

	if (*result && kref_get_unless_zero(&(*result)->refcount)) {
		rcu_read_unlock();
		return 0;
	}

	rcu_read_unlock();
	return -ENOENT;
}