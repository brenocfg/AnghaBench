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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  u_char ;
struct ndfc_controller {scalar_t__ ndfcbase; } ;
struct nand_chip {int dummy; } ;

/* Variables and functions */
 scalar_t__ NDFC_ECC ; 
 int /*<<< orphan*/  in_be32 (scalar_t__) ; 
 struct ndfc_controller* nand_get_controller_data (struct nand_chip*) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int ndfc_calculate_ecc(struct nand_chip *chip,
			      const u_char *dat, u_char *ecc_code)
{
	struct ndfc_controller *ndfc = nand_get_controller_data(chip);
	uint32_t ecc;
	uint8_t *p = (uint8_t *)&ecc;

	wmb();
	ecc = in_be32(ndfc->ndfcbase + NDFC_ECC);
	/* The NDFC uses Smart Media (SMC) bytes order */
	ecc_code[0] = p[1];
	ecc_code[1] = p[2];
	ecc_code[2] = p[3];

	return 0;
}