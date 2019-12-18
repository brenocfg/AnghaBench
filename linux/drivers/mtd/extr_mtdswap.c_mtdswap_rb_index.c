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
struct rb_root {int dummy; } ;
struct rb_node {int dummy; } ;

/* Variables and functions */
 struct rb_node* rb_first (struct rb_root*) ; 
 struct rb_node* rb_next (struct rb_node*) ; 

__attribute__((used)) static struct rb_node *mtdswap_rb_index(struct rb_root *root, unsigned int idx)
{
	struct rb_node *p;
	unsigned int i;

	p = rb_first(root);
	i = 0;
	while (i < idx && p) {
		p = rb_next(p);
		i++;
	}

	return p;
}