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
struct spi_master {int dummy; } ;
struct pl022 {int /*<<< orphan*/  virtbase; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSP_CR1 (int /*<<< orphan*/ ) ; 
 int SSP_CR1_MASK_SSE ; 
 int readw (int /*<<< orphan*/ ) ; 
 struct pl022* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  writew (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pl022_unprepare_transfer_hardware(struct spi_master *master)
{
	struct pl022 *pl022 = spi_master_get_devdata(master);

	/* nothing more to do - disable spi/ssp and power off */
	writew((readw(SSP_CR1(pl022->virtbase)) &
		(~SSP_CR1_MASK_SSE)), SSP_CR1(pl022->virtbase));

	return 0;
}