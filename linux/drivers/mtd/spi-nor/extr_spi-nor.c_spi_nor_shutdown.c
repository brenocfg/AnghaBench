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
struct spi_mem {int dummy; } ;

/* Variables and functions */
 struct spi_nor* spi_mem_get_drvdata (struct spi_mem*) ; 
 int /*<<< orphan*/  spi_nor_restore (struct spi_nor*) ; 

__attribute__((used)) static void spi_nor_shutdown(struct spi_mem *spimem)
{
	struct spi_nor *nor = spi_mem_get_drvdata(spimem);

	spi_nor_restore(nor);
}