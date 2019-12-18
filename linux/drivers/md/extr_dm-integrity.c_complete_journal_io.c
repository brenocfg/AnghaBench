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
struct journal_completion {int /*<<< orphan*/  ic; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  complete_journal_op (struct journal_completion*) ; 
 int /*<<< orphan*/  dm_integrity_io_error (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void complete_journal_io(unsigned long error, void *context)
{
	struct journal_completion *comp = context;
	if (unlikely(error != 0))
		dm_integrity_io_error(comp->ic, "writing journal", -EIO);
	complete_journal_op(comp);
}