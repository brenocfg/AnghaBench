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
struct btree_write {int dummy; } ;
struct btree {struct btree_write* writes; } ;

/* Variables and functions */
 int btree_node_write_idx (struct btree*) ; 

__attribute__((used)) static inline struct btree_write *btree_prev_write(struct btree *b)
{
	return b->writes + (btree_node_write_idx(b) ^ 1);
}