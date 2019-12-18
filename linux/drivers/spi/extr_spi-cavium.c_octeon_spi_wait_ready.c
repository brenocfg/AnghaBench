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
struct TYPE_2__ {scalar_t__ busy; } ;
union cvmx_mpi_sts {int /*<<< orphan*/  u64; TYPE_1__ s; } ;
struct octeon_spi {scalar_t__ register_base; } ;

/* Variables and functions */
 scalar_t__ OCTEON_SPI_STS (struct octeon_spi*) ; 
 int /*<<< orphan*/  __delay (int) ; 
 int /*<<< orphan*/  readq (scalar_t__) ; 

__attribute__((used)) static void octeon_spi_wait_ready(struct octeon_spi *p)
{
	union cvmx_mpi_sts mpi_sts;
	unsigned int loops = 0;

	do {
		if (loops++)
			__delay(500);
		mpi_sts.u64 = readq(p->register_base + OCTEON_SPI_STS(p));
	} while (mpi_sts.s.busy);
}