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
struct vf610_nfc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_16BIT ; 
 int /*<<< orphan*/  CONFIG_ADDR_AUTO_INCR_BIT ; 
 int /*<<< orphan*/  CONFIG_BOOT_MODE_BIT ; 
 int /*<<< orphan*/  CONFIG_BUFNO_AUTO_INCR_BIT ; 
 int /*<<< orphan*/  CONFIG_DMA_REQ_BIT ; 
 int /*<<< orphan*/  CONFIG_FAST_FLASH_BIT ; 
 int /*<<< orphan*/  CONFIG_PAGE_CNT_MASK ; 
 int /*<<< orphan*/  CONFIG_PAGE_CNT_SHIFT ; 
 int /*<<< orphan*/  ECC_BYPASS ; 
 int /*<<< orphan*/  NFC_FLASH_CONFIG ; 
 int /*<<< orphan*/  vf610_nfc_clear (struct vf610_nfc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vf610_nfc_ecc_mode (struct vf610_nfc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vf610_nfc_set (struct vf610_nfc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vf610_nfc_set_field (struct vf610_nfc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void vf610_nfc_preinit_controller(struct vf610_nfc *nfc)
{
	vf610_nfc_clear(nfc, NFC_FLASH_CONFIG, CONFIG_16BIT);
	vf610_nfc_clear(nfc, NFC_FLASH_CONFIG, CONFIG_ADDR_AUTO_INCR_BIT);
	vf610_nfc_clear(nfc, NFC_FLASH_CONFIG, CONFIG_BUFNO_AUTO_INCR_BIT);
	vf610_nfc_clear(nfc, NFC_FLASH_CONFIG, CONFIG_BOOT_MODE_BIT);
	vf610_nfc_clear(nfc, NFC_FLASH_CONFIG, CONFIG_DMA_REQ_BIT);
	vf610_nfc_set(nfc, NFC_FLASH_CONFIG, CONFIG_FAST_FLASH_BIT);
	vf610_nfc_ecc_mode(nfc, ECC_BYPASS);

	/* Disable virtual pages, only one elementary transfer unit */
	vf610_nfc_set_field(nfc, NFC_FLASH_CONFIG, CONFIG_PAGE_CNT_MASK,
			    CONFIG_PAGE_CNT_SHIFT, 1);
}