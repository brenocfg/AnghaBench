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
struct spi_nor {int dummy; } ;

/* Variables and functions */
 int macronix_set_4byte (struct spi_nor*,int) ; 
 int spi_nor_write_ear (struct spi_nor*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_disable (struct spi_nor*) ; 
 int /*<<< orphan*/  write_enable (struct spi_nor*) ; 

__attribute__((used)) static int winbond_set_4byte(struct spi_nor *nor, bool enable)
{
	int ret;

	ret = macronix_set_4byte(nor, enable);
	if (ret || enable)
		return ret;

	/*
	 * On Winbond W25Q256FV, leaving 4byte mode causes the Extended Address
	 * Register to be set to 1, so all 3-byte-address reads come from the
	 * second 16M. We must clear the register to enable normal behavior.
	 */
	write_enable(nor);
	ret = spi_nor_write_ear(nor, 0);
	write_disable(nor);

	return ret;
}