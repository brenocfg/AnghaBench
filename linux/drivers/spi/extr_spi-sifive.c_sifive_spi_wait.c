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
typedef  int u32 ;
struct sifive_spi {int /*<<< orphan*/  done; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIFIVE_SPI_REG_IE ; 
 int /*<<< orphan*/  SIFIVE_SPI_REG_IP ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int sifive_spi_read (struct sifive_spi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sifive_spi_write (struct sifive_spi*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sifive_spi_wait(struct sifive_spi *spi, u32 bit, int poll)
{
	if (poll) {
		u32 cr;

		do {
			cr = sifive_spi_read(spi, SIFIVE_SPI_REG_IP);
		} while (!(cr & bit));
	} else {
		reinit_completion(&spi->done);
		sifive_spi_write(spi, SIFIVE_SPI_REG_IE, bit);
		wait_for_completion(&spi->done);
	}
}