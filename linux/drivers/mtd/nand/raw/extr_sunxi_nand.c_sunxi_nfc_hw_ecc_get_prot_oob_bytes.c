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
typedef  int /*<<< orphan*/  u8 ;
struct sunxi_nfc {scalar_t__ regs; } ;
struct nand_chip {int options; int /*<<< orphan*/  controller; } ;

/* Variables and functions */
 int NAND_NEED_SCRAMBLING ; 
 scalar_t__ NFC_REG_USER_DATA (int) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  sunxi_nfc_randomize_bbm (struct nand_chip*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sunxi_nfc_user_data_to_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct sunxi_nfc* to_sunxi_nfc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sunxi_nfc_hw_ecc_get_prot_oob_bytes(struct nand_chip *nand, u8 *oob,
						int step, bool bbm, int page)
{
	struct sunxi_nfc *nfc = to_sunxi_nfc(nand->controller);

	sunxi_nfc_user_data_to_buf(readl(nfc->regs + NFC_REG_USER_DATA(step)),
				   oob);

	/* De-randomize the Bad Block Marker. */
	if (bbm && (nand->options & NAND_NEED_SCRAMBLING))
		sunxi_nfc_randomize_bbm(nand, page, oob);
}