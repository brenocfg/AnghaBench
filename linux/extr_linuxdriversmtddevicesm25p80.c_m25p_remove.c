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
struct spi_mem {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mtd; } ;
struct m25p {TYPE_1__ spi_nor; } ;

/* Variables and functions */
 int mtd_device_unregister (int /*<<< orphan*/ *) ; 
 struct m25p* spi_mem_get_drvdata (struct spi_mem*) ; 
 int /*<<< orphan*/  spi_nor_restore (TYPE_1__*) ; 

__attribute__((used)) static int m25p_remove(struct spi_mem *spimem)
{
	struct m25p	*flash = spi_mem_get_drvdata(spimem);

	spi_nor_restore(&flash->spi_nor);

	/* Clean up MTD stuff. */
	return mtd_device_unregister(&flash->spi_nor.mtd);
}