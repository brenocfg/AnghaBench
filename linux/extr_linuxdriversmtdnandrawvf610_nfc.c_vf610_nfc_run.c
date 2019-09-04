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
typedef  int /*<<< orphan*/  u32 ;
struct vf610_nfc {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  COL_ADDR_MASK ; 
 int /*<<< orphan*/  COL_ADDR_SHIFT ; 
 int /*<<< orphan*/  NFC_COL_ADDR ; 
 int /*<<< orphan*/  NFC_FLASH_CMD1 ; 
 int /*<<< orphan*/  NFC_FLASH_CMD2 ; 
 int /*<<< orphan*/  NFC_ROW_ADDR ; 
 int /*<<< orphan*/  NFC_SECTOR_SIZE ; 
 int /*<<< orphan*/  ROW_ADDR_MASK ; 
 int /*<<< orphan*/  ROW_ADDR_SHIFT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vf610_nfc_done (struct vf610_nfc*) ; 
 int /*<<< orphan*/  vf610_nfc_set_field (struct vf610_nfc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vf610_nfc_write (struct vf610_nfc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void vf610_nfc_run(struct vf610_nfc *nfc, u32 col, u32 row,
				 u32 cmd1, u32 cmd2, u32 trfr_sz)
{
	vf610_nfc_set_field(nfc, NFC_COL_ADDR, COL_ADDR_MASK,
			    COL_ADDR_SHIFT, col);

	vf610_nfc_set_field(nfc, NFC_ROW_ADDR, ROW_ADDR_MASK,
			    ROW_ADDR_SHIFT, row);

	vf610_nfc_write(nfc, NFC_SECTOR_SIZE, trfr_sz);
	vf610_nfc_write(nfc, NFC_FLASH_CMD1, cmd1);
	vf610_nfc_write(nfc, NFC_FLASH_CMD2, cmd2);

	dev_dbg(nfc->dev,
		"col 0x%04x, row 0x%08x, cmd1 0x%08x, cmd2 0x%08x, len %d\n",
		col, row, cmd1, cmd2, trfr_sz);

	vf610_nfc_done(nfc);
}