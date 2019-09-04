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
struct resize {int /*<<< orphan*/  root; int /*<<< orphan*/  value; int /*<<< orphan*/  new_nr_entries_in_last_block; int /*<<< orphan*/  new_nr_full_blocks; int /*<<< orphan*/  max_entries; int /*<<< orphan*/  size_of_block; int /*<<< orphan*/  info; } ;

/* Variables and functions */
 int insert_new_ablock (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int grow_add_tail_block(struct resize *resize)
{
	return insert_new_ablock(resize->info, resize->size_of_block,
				 resize->max_entries,
				 resize->new_nr_full_blocks,
				 resize->new_nr_entries_in_last_block,
				 resize->value, &resize->root);
}