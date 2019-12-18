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
struct spi_engine_program {int dummy; } ;
struct spi_device {int /*<<< orphan*/  chip_select; } ;

/* Variables and functions */
 unsigned int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_ENGINE_CMD_ASSERT (int,unsigned int) ; 
 int /*<<< orphan*/  spi_engine_program_add_cmd (struct spi_engine_program*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void spi_engine_gen_cs(struct spi_engine_program *p, bool dry,
		struct spi_device *spi, bool assert)
{
	unsigned int mask = 0xff;

	if (assert)
		mask ^= BIT(spi->chip_select);

	spi_engine_program_add_cmd(p, dry, SPI_ENGINE_CMD_ASSERT(1, mask));
}