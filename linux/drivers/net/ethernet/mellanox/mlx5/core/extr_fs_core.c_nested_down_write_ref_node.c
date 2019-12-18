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
struct fs_node {int /*<<< orphan*/  refcount; int /*<<< orphan*/  lock; } ;
typedef  enum fs_i_lock_class { ____Placeholder_fs_i_lock_class } fs_i_lock_class ;

/* Variables and functions */
 int /*<<< orphan*/  down_write_nested (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nested_down_write_ref_node(struct fs_node *node,
				       enum fs_i_lock_class class)
{
	if (node) {
		down_write_nested(&node->lock, class);
		refcount_inc(&node->refcount);
	}
}