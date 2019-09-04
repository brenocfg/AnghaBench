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
struct si_sm_io {int /*<<< orphan*/  io_size; scalar_t__ addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  mem_region_cleanup (struct si_sm_io*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mem_cleanup(struct si_sm_io *io)
{
	if (io->addr) {
		iounmap(io->addr);
		mem_region_cleanup(io, io->io_size);
	}
}