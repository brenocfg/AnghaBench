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
struct marvell_nand_chip_sel {int dummy; } ;
struct marvell_nand_chip {size_t selected_die; struct marvell_nand_chip_sel* sels; } ;

/* Variables and functions */

__attribute__((used)) static inline struct marvell_nand_chip_sel *to_nand_sel(struct marvell_nand_chip
							*nand)
{
	return &nand->sels[nand->selected_die];
}