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
struct tango_nfc {scalar_t__ reg_base; } ;
struct tango_chip {int /*<<< orphan*/  bb_cfg; int /*<<< orphan*/  pkt_n_cfg; int /*<<< orphan*/  pkt_0_cfg; int /*<<< orphan*/  xfer_cfg; int /*<<< orphan*/  timing2; int /*<<< orphan*/  timing1; } ;
struct nand_chip {int /*<<< orphan*/  controller; } ;

/* Variables and functions */
 scalar_t__ NFC_BB_CFG ; 
 scalar_t__ NFC_PKT_0_CFG ; 
 scalar_t__ NFC_PKT_N_CFG ; 
 scalar_t__ NFC_TIMING1 ; 
 scalar_t__ NFC_TIMING2 ; 
 scalar_t__ NFC_XFER_CFG ; 
 struct tango_chip* to_tango_chip (struct nand_chip*) ; 
 struct tango_nfc* to_tango_nfc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void tango_select_chip(struct nand_chip *chip, int idx)
{
	struct tango_nfc *nfc = to_tango_nfc(chip->controller);
	struct tango_chip *tchip = to_tango_chip(chip);

	if (idx < 0)
		return; /* No "chip unselect" function */

	writel_relaxed(tchip->timing1, nfc->reg_base + NFC_TIMING1);
	writel_relaxed(tchip->timing2, nfc->reg_base + NFC_TIMING2);
	writel_relaxed(tchip->xfer_cfg, nfc->reg_base + NFC_XFER_CFG);
	writel_relaxed(tchip->pkt_0_cfg, nfc->reg_base + NFC_PKT_0_CFG);
	writel_relaxed(tchip->pkt_n_cfg, nfc->reg_base + NFC_PKT_N_CFG);
	writel_relaxed(tchip->bb_cfg, nfc->reg_base + NFC_BB_CFG);
}