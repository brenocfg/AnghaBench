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
struct list_head {struct list_head* next; struct list_head* prev; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (struct list_head*) ; 

__attribute__((used)) static inline struct list_head *lio_list_delete_head(struct list_head *root)
{
	struct list_head *node;

	if (root->prev == root && root->next == root)
		node = NULL;
	else
		node = root->next;

	if (node)
		list_del(node);

	return node;
}