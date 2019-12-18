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
typedef  int /*<<< orphan*/  user_data ;
typedef  int /*<<< orphan*/  u8 ;
struct sunxi_nfc {scalar_t__ regs; } ;
struct nand_chip {int options; int /*<<< orphan*/  controller; } ;

/* Variables and functions */
 int NAND_NEED_SCRAMBLING ; 
 scalar_t__ NFC_REG_USER_DATA (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  sunxi_nfc_buf_to_user_data (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  sunxi_nfc_randomize_bbm (struct nand_chip*,int,int /*<<< orphan*/ *) ; 
 struct sunxi_nfc* to_sunxi_nfc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void sunxi_nfc_hw_ecc_set_prot_oob_bytes(struct nand_chip *nand,
						const u8 *oob, int step,
						bool bbm, int page)
{
	struct sunxi_nfc *nfc = to_sunxi_nfc(nand->controller);
	u8 user_data[4];

	/* Randomize the Bad Block Marker. */
	if (bbm && (nand->options & NAND_NEED_SCRAMBLING)) {
		memcpy(user_data, oob, sizeof(user_data));
		sunxi_nfc_randomize_bbm(nand, page, user_data);
		oob = user_data;
	}

	writel(sunxi_nfc_buf_to_user_data(oob),
	       nfc->regs + NFC_REG_USER_DATA(step));
}