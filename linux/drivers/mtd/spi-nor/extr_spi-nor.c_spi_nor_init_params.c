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
struct spi_nor {TYPE_1__* info; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int SPI_NOR_DUAL_READ ; 
 int SPI_NOR_QUAD_READ ; 
 int SPI_NOR_SKIP_SFDP ; 
 int /*<<< orphan*/  spi_nor_info_init_params (struct spi_nor*) ; 
 int /*<<< orphan*/  spi_nor_late_init_params (struct spi_nor*) ; 
 int /*<<< orphan*/  spi_nor_manufacturer_init_params (struct spi_nor*) ; 
 int /*<<< orphan*/  spi_nor_post_sfdp_fixups (struct spi_nor*) ; 
 int /*<<< orphan*/  spi_nor_sfdp_init_params (struct spi_nor*) ; 

__attribute__((used)) static void spi_nor_init_params(struct spi_nor *nor)
{
	spi_nor_info_init_params(nor);

	spi_nor_manufacturer_init_params(nor);

	if ((nor->info->flags & (SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ)) &&
	    !(nor->info->flags & SPI_NOR_SKIP_SFDP))
		spi_nor_sfdp_init_params(nor);

	spi_nor_post_sfdp_fixups(nor);

	spi_nor_late_init_params(nor);
}