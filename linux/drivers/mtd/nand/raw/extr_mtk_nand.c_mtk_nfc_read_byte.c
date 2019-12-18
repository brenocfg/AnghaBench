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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct nand_chip {int dummy; } ;
struct mtk_nfc {TYPE_1__* caps; } ;
struct TYPE_2__ {int max_sector; } ;

/* Variables and functions */
 int CNFG_BYTE_RW ; 
 int CNFG_READ_EN ; 
 int CON_BRD ; 
 int CON_SEC_SHIFT ; 
 int /*<<< orphan*/  NFI_CNFG ; 
 int /*<<< orphan*/  NFI_CON ; 
 int /*<<< orphan*/  NFI_DATAR ; 
 int NFI_FSM_CUSTDATA ; 
 int NFI_FSM_MASK ; 
 int /*<<< orphan*/  NFI_STA ; 
 int /*<<< orphan*/  NFI_STRDATA ; 
 int STAR_EN ; 
 int /*<<< orphan*/  mtk_nfc_wait_ioready (struct mtk_nfc*) ; 
 struct mtk_nfc* nand_get_controller_data (struct nand_chip*) ; 
 int /*<<< orphan*/  nfi_readb (struct mtk_nfc*,int /*<<< orphan*/ ) ; 
 int nfi_readl (struct mtk_nfc*,int /*<<< orphan*/ ) ; 
 int nfi_readw (struct mtk_nfc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfi_writel (struct mtk_nfc*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfi_writew (struct mtk_nfc*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u8 mtk_nfc_read_byte(struct nand_chip *chip)
{
	struct mtk_nfc *nfc = nand_get_controller_data(chip);
	u32 reg;

	/* after each byte read, the NFI_STA reg is reset by the hardware */
	reg = nfi_readl(nfc, NFI_STA) & NFI_FSM_MASK;
	if (reg != NFI_FSM_CUSTDATA) {
		reg = nfi_readw(nfc, NFI_CNFG);
		reg |= CNFG_BYTE_RW | CNFG_READ_EN;
		nfi_writew(nfc, reg, NFI_CNFG);

		/*
		 * set to max sector to allow the HW to continue reading over
		 * unaligned accesses
		 */
		reg = (nfc->caps->max_sector << CON_SEC_SHIFT) | CON_BRD;
		nfi_writel(nfc, reg, NFI_CON);

		/* trigger to fetch data */
		nfi_writew(nfc, STAR_EN, NFI_STRDATA);
	}

	mtk_nfc_wait_ioready(nfc);

	return nfi_readb(nfc, NFI_DATAR);
}