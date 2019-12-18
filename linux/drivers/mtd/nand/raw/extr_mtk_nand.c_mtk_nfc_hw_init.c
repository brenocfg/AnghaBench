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
struct mtk_nfc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFI_CNRNB ; 
 int /*<<< orphan*/  NFI_INTR_EN ; 
 int /*<<< orphan*/  NFI_INTR_STA ; 
 int /*<<< orphan*/  NFI_PAGEFMT ; 
 int /*<<< orphan*/  PAGEFMT_8K_16K ; 
 int /*<<< orphan*/  mtk_nfc_hw_reset (struct mtk_nfc*) ; 
 int /*<<< orphan*/  nfi_readl (struct mtk_nfc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfi_writel (struct mtk_nfc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfi_writew (struct mtk_nfc*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void mtk_nfc_hw_init(struct mtk_nfc *nfc)
{
	/*
	 * CNRNB: nand ready/busy register
	 * -------------------------------
	 * 7:4: timeout register for polling the NAND busy/ready signal
	 * 0  : poll the status of the busy/ready signal after [7:4]*16 cycles.
	 */
	nfi_writew(nfc, 0xf1, NFI_CNRNB);
	nfi_writel(nfc, PAGEFMT_8K_16K, NFI_PAGEFMT);

	mtk_nfc_hw_reset(nfc);

	nfi_readl(nfc, NFI_INTR_STA);
	nfi_writel(nfc, 0, NFI_INTR_EN);
}