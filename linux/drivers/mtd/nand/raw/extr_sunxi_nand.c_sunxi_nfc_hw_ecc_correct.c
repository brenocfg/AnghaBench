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
typedef  int u8 ;
typedef  int u32 ;
struct sunxi_nfc {scalar_t__ regs; } ;
struct nand_ecc_ctrl {scalar_t__ bytes; scalar_t__ size; } ;
struct nand_chip {struct nand_ecc_ctrl ecc; int /*<<< orphan*/  controller; } ;

/* Variables and functions */
 int EBADMSG ; 
 int NFC_ECC_ERR (int) ; 
 int NFC_ECC_ERR_CNT (int,int) ; 
 int NFC_ECC_PAT_FOUND (int) ; 
 scalar_t__ NFC_REG_ECC_ERR_CNT (int) ; 
 scalar_t__ NFC_REG_PAT_ID ; 
 int /*<<< orphan*/  memset (int*,int,scalar_t__) ; 
 int readl (scalar_t__) ; 
 struct sunxi_nfc* to_sunxi_nfc (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int sunxi_nfc_hw_ecc_correct(struct nand_chip *nand, u8 *data, u8 *oob,
				    int step, u32 status, bool *erased)
{
	struct sunxi_nfc *nfc = to_sunxi_nfc(nand->controller);
	struct nand_ecc_ctrl *ecc = &nand->ecc;
	u32 tmp;

	*erased = false;

	if (status & NFC_ECC_ERR(step))
		return -EBADMSG;

	if (status & NFC_ECC_PAT_FOUND(step)) {
		u8 pattern;

		if (unlikely(!(readl(nfc->regs + NFC_REG_PAT_ID) & 0x1))) {
			pattern = 0x0;
		} else {
			pattern = 0xff;
			*erased = true;
		}

		if (data)
			memset(data, pattern, ecc->size);

		if (oob)
			memset(oob, pattern, ecc->bytes + 4);

		return 0;
	}

	tmp = readl(nfc->regs + NFC_REG_ECC_ERR_CNT(step));

	return NFC_ECC_ERR_CNT(step, tmp);
}