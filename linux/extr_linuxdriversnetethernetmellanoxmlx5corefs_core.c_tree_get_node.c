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
struct fs_node {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int refcount_inc_not_zero (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tree_get_node(struct fs_node *node)
{
	return refcount_inc_not_zero(&node->refcount);
}