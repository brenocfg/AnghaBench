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
typedef  int u16 ;
struct mtk_nfc {int /*<<< orphan*/  done; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  NFI_INTR_EN ; 
 int /*<<< orphan*/  NFI_INTR_STA ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int nfi_readw (struct mtk_nfc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfi_writew (struct mtk_nfc*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t mtk_nfc_irq(int irq, void *id)
{
	struct mtk_nfc *nfc = id;
	u16 sta, ien;

	sta = nfi_readw(nfc, NFI_INTR_STA);
	ien = nfi_readw(nfc, NFI_INTR_EN);

	if (!(sta & ien))
		return IRQ_NONE;

	nfi_writew(nfc, ~sta & ien, NFI_INTR_EN);
	complete(&nfc->done);

	return IRQ_HANDLED;
}