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
struct bset_tree {int /*<<< orphan*/  extra; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 unsigned int __to_inorder (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int to_inorder(unsigned int j, struct bset_tree *t)
{
	return __to_inorder(j, t->size, t->extra);
}