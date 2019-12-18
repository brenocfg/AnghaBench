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
struct uverbs_api_object {int dummy; } ;
struct ib_uverbs_file {int /*<<< orphan*/  idr; } ;
struct ib_uobject {int /*<<< orphan*/  ref; } ;
typedef  scalar_t__ s64 ;
typedef  enum rdma_lookup_mode { ____Placeholder_rdma_lookup_mode } rdma_lookup_mode ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOENT ; 
 struct ib_uobject* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ ULONG_MAX ; 
 int /*<<< orphan*/  kref_get_unless_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct ib_uobject* xa_load (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static struct ib_uobject *
lookup_get_idr_uobject(const struct uverbs_api_object *obj,
		       struct ib_uverbs_file *ufile, s64 id,
		       enum rdma_lookup_mode mode)
{
	struct ib_uobject *uobj;

	if (id < 0 || id > ULONG_MAX)
		return ERR_PTR(-EINVAL);

	rcu_read_lock();
	/*
	 * The idr_find is guaranteed to return a pointer to something that
	 * isn't freed yet, or NULL, as the free after idr_remove goes through
	 * kfree_rcu(). However the object may still have been released and
	 * kfree() could be called at any time.
	 */
	uobj = xa_load(&ufile->idr, id);
	if (!uobj || !kref_get_unless_zero(&uobj->ref))
		uobj = ERR_PTR(-ENOENT);
	rcu_read_unlock();
	return uobj;
}