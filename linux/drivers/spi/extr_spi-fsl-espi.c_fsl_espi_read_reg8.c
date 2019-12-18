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
typedef  int /*<<< orphan*/  u8 ;
struct fsl_espi {scalar_t__ reg_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  ioread8 (scalar_t__) ; 

__attribute__((used)) static inline u8 fsl_espi_read_reg8(struct fsl_espi *espi, int offset)
{
	return ioread8(espi->reg_base + offset);
}