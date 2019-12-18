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
struct lpi_range {scalar_t__ base_id; scalar_t__ span; int /*<<< orphan*/  entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct lpi_range*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpi_range_list ; 

__attribute__((used)) static void merge_lpi_ranges(struct lpi_range *a, struct lpi_range *b)
{
	if (&a->entry == &lpi_range_list || &b->entry == &lpi_range_list)
		return;
	if (a->base_id + a->span != b->base_id)
		return;
	b->base_id = a->base_id;
	b->span += a->span;
	list_del(&a->entry);
	kfree(a);
}