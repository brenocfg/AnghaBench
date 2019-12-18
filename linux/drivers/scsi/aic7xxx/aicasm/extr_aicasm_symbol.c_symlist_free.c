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
typedef  int /*<<< orphan*/  symlist_t ;
typedef  int /*<<< orphan*/  symbol_node_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SLIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SLIST_NEXT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  links ; 

void
symlist_free(symlist_t *symlist)
{
	symbol_node_t *node1, *node2;

	node1 = SLIST_FIRST(symlist);
	while (node1 != NULL) {
		node2 = SLIST_NEXT(node1, links);
		free(node1);
		node1 = node2;
	}
	SLIST_INIT(symlist);
}