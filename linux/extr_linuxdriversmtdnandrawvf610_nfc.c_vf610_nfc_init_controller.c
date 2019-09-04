#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ mode; } ;
struct TYPE_4__ {int options; TYPE_1__ ecc; } ;
struct vf610_nfc {TYPE_2__ chip; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_16BIT ; 
 int /*<<< orphan*/  CONFIG_ECC_SRAM_ADDR_MASK ; 
 int /*<<< orphan*/  CONFIG_ECC_SRAM_ADDR_SHIFT ; 
 int /*<<< orphan*/  CONFIG_ECC_SRAM_REQ_BIT ; 
 int ECC_SRAM_ADDR ; 
 int NAND_BUSWIDTH_16 ; 
 scalar_t__ NAND_ECC_HW ; 
 int /*<<< orphan*/  NFC_FLASH_CONFIG ; 
 int /*<<< orphan*/  vf610_nfc_clear (struct vf610_nfc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vf610_nfc_set (struct vf610_nfc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vf610_nfc_set_field (struct vf610_nfc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void vf610_nfc_init_controller(struct vf610_nfc *nfc)
{
	if (nfc->chip.options & NAND_BUSWIDTH_16)
		vf610_nfc_set(nfc, NFC_FLASH_CONFIG, CONFIG_16BIT);
	else
		vf610_nfc_clear(nfc, NFC_FLASH_CONFIG, CONFIG_16BIT);

	if (nfc->chip.ecc.mode == NAND_ECC_HW) {
		/* Set ECC status offset in SRAM */
		vf610_nfc_set_field(nfc, NFC_FLASH_CONFIG,
				    CONFIG_ECC_SRAM_ADDR_MASK,
				    CONFIG_ECC_SRAM_ADDR_SHIFT,
				    ECC_SRAM_ADDR >> 3);

		/* Enable ECC status in SRAM */
		vf610_nfc_set(nfc, NFC_FLASH_CONFIG, CONFIG_ECC_SRAM_REQ_BIT);
	}
}