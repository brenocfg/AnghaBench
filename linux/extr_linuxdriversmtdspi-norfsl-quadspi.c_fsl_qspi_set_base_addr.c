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
struct fsl_qspi {int chip_base_addr; int nor_size; struct spi_nor* nor; } ;

/* Variables and functions */

__attribute__((used)) static void fsl_qspi_set_base_addr(struct fsl_qspi *q, struct spi_nor *nor)
{
	q->chip_base_addr = q->nor_size * (nor - q->nor);
}