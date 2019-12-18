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
struct stm32_fmc2_nfc {scalar_t__ dma_ecc_ch; scalar_t__ dma_rx_ch; scalar_t__ dma_tx_ch; } ;
struct TYPE_2__ {scalar_t__ strength; int bytes; int /*<<< orphan*/  read_page; int /*<<< orphan*/  correct; int /*<<< orphan*/  calculate; int /*<<< orphan*/  options; int /*<<< orphan*/  hwctl; int /*<<< orphan*/  read_page_raw; int /*<<< orphan*/  write_page_raw; int /*<<< orphan*/  write_page; } ;
struct nand_chip {int options; TYPE_1__ ecc; int /*<<< orphan*/  controller; } ;

/* Variables and functions */
 scalar_t__ FMC2_ECC_BCH8 ; 
 scalar_t__ FMC2_ECC_HAM ; 
 int NAND_BUSWIDTH_16 ; 
 int /*<<< orphan*/  NAND_ECC_GENERIC_ERASED_CHECK ; 
 int /*<<< orphan*/  stm32_fmc2_bch_calculate ; 
 int /*<<< orphan*/  stm32_fmc2_bch_correct ; 
 int /*<<< orphan*/  stm32_fmc2_ham_calculate ; 
 int /*<<< orphan*/  stm32_fmc2_ham_correct ; 
 int /*<<< orphan*/  stm32_fmc2_hwctl ; 
 int /*<<< orphan*/  stm32_fmc2_read_page ; 
 int /*<<< orphan*/  stm32_fmc2_sequencer_correct ; 
 int /*<<< orphan*/  stm32_fmc2_sequencer_read_page ; 
 int /*<<< orphan*/  stm32_fmc2_sequencer_read_page_raw ; 
 int /*<<< orphan*/  stm32_fmc2_sequencer_write_page ; 
 int /*<<< orphan*/  stm32_fmc2_sequencer_write_page_raw ; 
 struct stm32_fmc2_nfc* to_stm32_nfc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stm32_fmc2_nand_callbacks_setup(struct nand_chip *chip)
{
	struct stm32_fmc2_nfc *fmc2 = to_stm32_nfc(chip->controller);

	/*
	 * Specific callbacks to read/write a page depending on
	 * the mode (polling/sequencer) and the algo used (Hamming, BCH).
	 */
	if (fmc2->dma_tx_ch && fmc2->dma_rx_ch && fmc2->dma_ecc_ch) {
		/* DMA => use sequencer mode callbacks */
		chip->ecc.correct = stm32_fmc2_sequencer_correct;
		chip->ecc.write_page = stm32_fmc2_sequencer_write_page;
		chip->ecc.read_page = stm32_fmc2_sequencer_read_page;
		chip->ecc.write_page_raw = stm32_fmc2_sequencer_write_page_raw;
		chip->ecc.read_page_raw = stm32_fmc2_sequencer_read_page_raw;
	} else {
		/* No DMA => use polling mode callbacks */
		chip->ecc.hwctl = stm32_fmc2_hwctl;
		if (chip->ecc.strength == FMC2_ECC_HAM) {
			/* Hamming is used */
			chip->ecc.calculate = stm32_fmc2_ham_calculate;
			chip->ecc.correct = stm32_fmc2_ham_correct;
			chip->ecc.options |= NAND_ECC_GENERIC_ERASED_CHECK;
		} else {
			/* BCH is used */
			chip->ecc.calculate = stm32_fmc2_bch_calculate;
			chip->ecc.correct = stm32_fmc2_bch_correct;
			chip->ecc.read_page = stm32_fmc2_read_page;
		}
	}

	/* Specific configurations depending on the algo used */
	if (chip->ecc.strength == FMC2_ECC_HAM)
		chip->ecc.bytes = chip->options & NAND_BUSWIDTH_16 ? 4 : 3;
	else if (chip->ecc.strength == FMC2_ECC_BCH8)
		chip->ecc.bytes = chip->options & NAND_BUSWIDTH_16 ? 14 : 13;
	else
		chip->ecc.bytes = chip->options & NAND_BUSWIDTH_16 ? 8 : 7;
}