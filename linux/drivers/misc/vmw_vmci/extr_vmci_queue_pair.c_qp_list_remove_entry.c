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
struct qp_list {int dummy; } ;
struct qp_entry {int /*<<< orphan*/  list_item; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qp_list_remove_entry(struct qp_list *qp_list,
				 struct qp_entry *entry)
{
	if (entry)
		list_del(&entry->list_item);
}