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
typedef  int u32 ;
struct vf610_nfc {scalar_t__ variant; } ;
struct nand_chip {int dummy; } ;

/* Variables and functions */
 int BIT (unsigned int) ; 
 int /*<<< orphan*/  NFC_ROW_ADDR ; 
 scalar_t__ NFC_VFC610 ; 
 int ROW_ADDR_CHIP_SEL_MASK ; 
 int ROW_ADDR_CHIP_SEL_RB_MASK ; 
 int ROW_ADDR_CHIP_SEL_RB_SHIFT ; 
 int ROW_ADDR_CHIP_SEL_SHIFT ; 
 struct vf610_nfc* chip_to_nfc (struct nand_chip*) ; 
 int vf610_nfc_read (struct vf610_nfc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vf610_nfc_write (struct vf610_nfc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void vf610_nfc_select_target(struct nand_chip *chip, unsigned int cs)
{
	struct vf610_nfc *nfc = chip_to_nfc(chip);
	u32 tmp;

	/* Vybrid only (MPC5125 would have full RB and four CS) */
	if (nfc->variant != NFC_VFC610)
		return;

	tmp = vf610_nfc_read(nfc, NFC_ROW_ADDR);
	tmp &= ~(ROW_ADDR_CHIP_SEL_RB_MASK | ROW_ADDR_CHIP_SEL_MASK);
	tmp |= 1 << ROW_ADDR_CHIP_SEL_RB_SHIFT;
	tmp |= BIT(cs) << ROW_ADDR_CHIP_SEL_SHIFT;

	vf610_nfc_write(nfc, NFC_ROW_ADDR, tmp);
}