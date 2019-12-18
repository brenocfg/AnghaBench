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
struct spi_sh_data {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  SPI_SH_CR1 ; 
 int SPI_SH_RBE ; 
 int spi_sh_read (struct spi_sh_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int spi_sh_wait_receive_buffer(struct spi_sh_data *ss)
{
	int timeout = 100000;

	while (spi_sh_read(ss, SPI_SH_CR1) & SPI_SH_RBE) {
		udelay(10);
		if (timeout-- < 0)
			return -ETIMEDOUT;
	}
	return 0;
}