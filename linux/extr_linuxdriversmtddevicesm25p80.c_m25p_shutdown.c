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
struct spi_mem {int dummy; } ;
struct m25p {int /*<<< orphan*/  spi_nor; } ;

/* Variables and functions */
 struct m25p* spi_mem_get_drvdata (struct spi_mem*) ; 
 int /*<<< orphan*/  spi_nor_restore (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void m25p_shutdown(struct spi_mem *spimem)
{
	struct m25p *flash = spi_mem_get_drvdata(spimem);

	spi_nor_restore(&flash->spi_nor);
}