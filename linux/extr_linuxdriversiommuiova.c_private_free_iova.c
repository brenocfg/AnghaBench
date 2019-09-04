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
struct iova_domain {int /*<<< orphan*/  rbroot; int /*<<< orphan*/  iova_rbtree_lock; } ;
struct iova {int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  __cached_rbnode_delete_update (struct iova_domain*,struct iova*) ; 
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_iova_mem (struct iova*) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void private_free_iova(struct iova_domain *iovad, struct iova *iova)
{
	assert_spin_locked(&iovad->iova_rbtree_lock);
	__cached_rbnode_delete_update(iovad, iova);
	rb_erase(&iova->node, &iovad->rbroot);
	free_iova_mem(iova);
}