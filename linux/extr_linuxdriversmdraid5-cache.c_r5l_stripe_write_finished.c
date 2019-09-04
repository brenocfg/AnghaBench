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
struct stripe_head {struct r5l_io_unit* log_io; } ;
struct r5l_io_unit {int /*<<< orphan*/  pending_stripe; } ;

/* Variables and functions */
 int /*<<< orphan*/  __r5l_stripe_write_finished (struct r5l_io_unit*) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 

void r5l_stripe_write_finished(struct stripe_head *sh)
{
	struct r5l_io_unit *io;

	io = sh->log_io;
	sh->log_io = NULL;

	if (io && atomic_dec_and_test(&io->pending_stripe))
		__r5l_stripe_write_finished(io);
}