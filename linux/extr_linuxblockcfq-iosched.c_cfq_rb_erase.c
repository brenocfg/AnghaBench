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
struct rb_node {int dummy; } ;
struct cfq_rb_root {int /*<<< orphan*/  count; int /*<<< orphan*/  rb; struct rb_node* rb_rightmost; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_CLEAR_NODE (struct rb_node*) ; 
 int /*<<< orphan*/  rb_erase_cached (struct rb_node*,int /*<<< orphan*/ *) ; 
 struct rb_node* rb_prev (struct rb_node*) ; 

__attribute__((used)) static void cfq_rb_erase(struct rb_node *n, struct cfq_rb_root *root)
{
	if (root->rb_rightmost == n)
		root->rb_rightmost = rb_prev(n);

	rb_erase_cached(n, &root->rb);
	RB_CLEAR_NODE(n);

	--root->count;
}