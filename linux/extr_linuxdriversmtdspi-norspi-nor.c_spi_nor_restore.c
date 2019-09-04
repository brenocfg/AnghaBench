#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct spi_nor {int addr_width; int flags; TYPE_1__* info; } ;
struct TYPE_3__ {int flags; } ;

/* Variables and functions */
 scalar_t__ JEDEC_MFR (TYPE_1__*) ; 
 int SNOR_F_BROKEN_RESET ; 
 scalar_t__ SNOR_MFR_SPANSION ; 
 int SPI_NOR_4B_OPCODES ; 
 int /*<<< orphan*/  set_4byte (struct spi_nor*,TYPE_1__*,int /*<<< orphan*/ ) ; 

void spi_nor_restore(struct spi_nor *nor)
{
	/* restore the addressing mode */
	if ((nor->addr_width == 4) &&
	    (JEDEC_MFR(nor->info) != SNOR_MFR_SPANSION) &&
	    !(nor->info->flags & SPI_NOR_4B_OPCODES) &&
	    (nor->flags & SNOR_F_BROKEN_RESET))
		set_4byte(nor, nor->info, 0);
}