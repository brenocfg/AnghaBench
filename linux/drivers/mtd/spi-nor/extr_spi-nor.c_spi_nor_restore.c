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
struct TYPE_2__ {int /*<<< orphan*/  (* set_4byte ) (struct spi_nor*,int) ;} ;
struct spi_nor {int addr_width; int flags; TYPE_1__ params; } ;

/* Variables and functions */
 int SNOR_F_4B_OPCODES ; 
 int SNOR_F_BROKEN_RESET ; 
 int /*<<< orphan*/  stub1 (struct spi_nor*,int) ; 

void spi_nor_restore(struct spi_nor *nor)
{
	/* restore the addressing mode */
	if (nor->addr_width == 4 && !(nor->flags & SNOR_F_4B_OPCODES) &&
	    nor->flags & SNOR_F_BROKEN_RESET)
		nor->params.set_4byte(nor, false);
}