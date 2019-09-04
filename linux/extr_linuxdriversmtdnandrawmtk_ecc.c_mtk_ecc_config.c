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
typedef  size_t u32 ;
struct mtk_ecc_config {int strength; scalar_t__ op; int len; size_t mode; int sectors; int /*<<< orphan*/  addr; } ;
struct mtk_ecc {int sectors; scalar_t__ regs; TYPE_1__* caps; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {size_t num_ecc_strength; int* ecc_strength; size_t ecc_mode_shift; int parity_bits; } ;

/* Variables and functions */
 size_t DEC_CNFG_CORRECT ; 
 size_t DEC_EMPTY_EN ; 
 scalar_t__ ECC_DECCNFG ; 
 scalar_t__ ECC_ENCCNFG ; 
 scalar_t__ ECC_ENCDIADDR ; 
 scalar_t__ ECC_ENCODE ; 
 size_t ECC_MS_SHIFT ; 
 size_t ECC_NFI_MODE ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 size_t lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (size_t,scalar_t__) ; 

__attribute__((used)) static int mtk_ecc_config(struct mtk_ecc *ecc, struct mtk_ecc_config *config)
{
	u32 ecc_bit, dec_sz, enc_sz;
	u32 reg, i;

	for (i = 0; i < ecc->caps->num_ecc_strength; i++) {
		if (ecc->caps->ecc_strength[i] == config->strength)
			break;
	}

	if (i == ecc->caps->num_ecc_strength) {
		dev_err(ecc->dev, "invalid ecc strength %d\n",
			config->strength);
		return -EINVAL;
	}

	ecc_bit = i;

	if (config->op == ECC_ENCODE) {
		/* configure ECC encoder (in bits) */
		enc_sz = config->len << 3;

		reg = ecc_bit | (config->mode << ecc->caps->ecc_mode_shift);
		reg |= (enc_sz << ECC_MS_SHIFT);
		writel(reg, ecc->regs + ECC_ENCCNFG);

		if (config->mode != ECC_NFI_MODE)
			writel(lower_32_bits(config->addr),
			       ecc->regs + ECC_ENCDIADDR);

	} else {
		/* configure ECC decoder (in bits) */
		dec_sz = (config->len << 3) +
			 config->strength * ecc->caps->parity_bits;

		reg = ecc_bit | (config->mode << ecc->caps->ecc_mode_shift);
		reg |= (dec_sz << ECC_MS_SHIFT) | DEC_CNFG_CORRECT;
		reg |= DEC_EMPTY_EN;
		writel(reg, ecc->regs + ECC_DECCNFG);

		if (config->sectors)
			ecc->sectors = 1 << (config->sectors - 1);
	}

	return 0;
}