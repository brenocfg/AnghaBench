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
struct ndfc_controller {scalar_t__ ndfcbase; } ;
struct nand_chip {int dummy; } ;

/* Variables and functions */
 scalar_t__ NDFC_STAT ; 
 int NDFC_STAT_IS_READY ; 
 int in_be32 (scalar_t__) ; 
 struct ndfc_controller* nand_get_controller_data (struct nand_chip*) ; 

__attribute__((used)) static int ndfc_ready(struct nand_chip *chip)
{
	struct ndfc_controller *ndfc = nand_get_controller_data(chip);

	return in_be32(ndfc->ndfcbase + NDFC_STAT) & NDFC_STAT_IS_READY;
}