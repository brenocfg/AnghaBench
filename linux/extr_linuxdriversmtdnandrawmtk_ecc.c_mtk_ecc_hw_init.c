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
struct mtk_ecc {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ ECC_DECCON ; 
 int /*<<< orphan*/  ECC_DECODE ; 
 scalar_t__ ECC_ENCCON ; 
 int /*<<< orphan*/  ECC_ENCODE ; 
 int /*<<< orphan*/  ECC_OP_DISABLE ; 
 int /*<<< orphan*/  mtk_ecc_wait_idle (struct mtk_ecc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  writew (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void mtk_ecc_hw_init(struct mtk_ecc *ecc)
{
	mtk_ecc_wait_idle(ecc, ECC_ENCODE);
	writew(ECC_OP_DISABLE, ecc->regs + ECC_ENCCON);

	mtk_ecc_wait_idle(ecc, ECC_DECODE);
	writel(ECC_OP_DISABLE, ecc->regs + ECC_DECCON);
}