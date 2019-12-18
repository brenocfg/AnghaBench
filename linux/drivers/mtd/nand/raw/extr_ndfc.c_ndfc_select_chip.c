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
typedef  int /*<<< orphan*/  uint32_t ;
struct ndfc_controller {scalar_t__ ndfcbase; scalar_t__ chip_select; } ;
struct nand_chip {int dummy; } ;

/* Variables and functions */
 scalar_t__ NDFC_CCR ; 
 int /*<<< orphan*/  NDFC_CCR_BS (scalar_t__) ; 
 int /*<<< orphan*/  NDFC_CCR_BS_MASK ; 
 int /*<<< orphan*/  NDFC_CCR_RESET_CE ; 
 int /*<<< orphan*/  in_be32 (scalar_t__) ; 
 struct ndfc_controller* nand_get_controller_data (struct nand_chip*) ; 
 int /*<<< orphan*/  out_be32 (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ndfc_select_chip(struct nand_chip *nchip, int chip)
{
	uint32_t ccr;
	struct ndfc_controller *ndfc = nand_get_controller_data(nchip);

	ccr = in_be32(ndfc->ndfcbase + NDFC_CCR);
	if (chip >= 0) {
		ccr &= ~NDFC_CCR_BS_MASK;
		ccr |= NDFC_CCR_BS(chip + ndfc->chip_select);
	} else
		ccr |= NDFC_CCR_RESET_CE;
	out_be32(ndfc->ndfcbase + NDFC_CCR, ccr);
}