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
struct io {int /*<<< orphan*/  count; int /*<<< orphan*/  error_bits; } ;
typedef  scalar_t__ blk_status_t ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete_io (struct io*) ; 
 int /*<<< orphan*/  set_bit (unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dec_count(struct io *io, unsigned int region, blk_status_t error)
{
	if (error)
		set_bit(region, &io->error_bits);

	if (atomic_dec_and_test(&io->count))
		complete_io(io);
}