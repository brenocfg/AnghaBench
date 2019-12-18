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
typedef  int /*<<< orphan*/  uint32_t ;
struct ttm_object_device {int /*<<< orphan*/  idr; } ;
struct ttm_base_object {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 struct ttm_base_object* idr_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_get_unless_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

struct ttm_base_object *
ttm_base_object_lookup_for_ref(struct ttm_object_device *tdev, uint32_t key)
{
	struct ttm_base_object *base;

	rcu_read_lock();
	base = idr_find(&tdev->idr, key);

	if (base && !kref_get_unless_zero(&base->refcount))
		base = NULL;
	rcu_read_unlock();

	return base;
}