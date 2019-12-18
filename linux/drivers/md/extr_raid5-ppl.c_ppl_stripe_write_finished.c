#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct stripe_head {struct ppl_io_unit* ppl_io; } ;
struct ppl_io_unit {TYPE_1__* log; int /*<<< orphan*/  pending_stripes; } ;
struct TYPE_2__ {scalar_t__ disk_flush_bitmap; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ppl_do_flush (struct ppl_io_unit*) ; 
 int /*<<< orphan*/  ppl_io_unit_finished (struct ppl_io_unit*) ; 

void ppl_stripe_write_finished(struct stripe_head *sh)
{
	struct ppl_io_unit *io;

	io = sh->ppl_io;
	sh->ppl_io = NULL;

	if (io && atomic_dec_and_test(&io->pending_stripes)) {
		if (io->log->disk_flush_bitmap)
			ppl_do_flush(io);
		else
			ppl_io_unit_finished(io);
	}
}