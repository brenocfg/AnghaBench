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
struct journal_io {int /*<<< orphan*/  range; struct journal_completion* comp; } ;
struct journal_completion {struct dm_integrity_c* ic; } ;
struct dm_integrity_c {int /*<<< orphan*/  journal_io_mempool; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  complete_journal_op (struct journal_completion*) ; 
 int /*<<< orphan*/  dm_integrity_io_error (struct dm_integrity_c*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free (struct journal_io*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_range (struct dm_integrity_c*,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void complete_copy_from_journal(unsigned long error, void *context)
{
	struct journal_io *io = context;
	struct journal_completion *comp = io->comp;
	struct dm_integrity_c *ic = comp->ic;
	remove_range(ic, &io->range);
	mempool_free(io, &ic->journal_io_mempool);
	if (unlikely(error != 0))
		dm_integrity_io_error(ic, "copying from journal", -EIO);
	complete_journal_op(comp);
}