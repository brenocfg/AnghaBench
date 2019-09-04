#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {void* next; } ;
struct lkdtm_list {TYPE_1__ node; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (TYPE_1__*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  test_head ; 

void lkdtm_CORRUPT_LIST_DEL(void)
{
	LIST_HEAD(test_head);
	struct lkdtm_list item;
	void *target[2] = { };
	void *redirection = &target;

	list_add(&item.node, &test_head);

	pr_info("attempting good list removal\n");
	list_del(&item.node);

	pr_info("attempting corrupted list removal\n");
	list_add(&item.node, &test_head);

	/* As with the list_add() test above, this corrupts "next". */
	item.node.next = redirection;
	list_del(&item.node);

	if (target[0] == NULL && target[1] == NULL)
		pr_err("Overwrite did not happen, but no BUG?!\n");
	else
		pr_err("list_del() corruption not detected!\n");
}