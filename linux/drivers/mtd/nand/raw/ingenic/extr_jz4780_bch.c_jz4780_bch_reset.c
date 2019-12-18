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
typedef  int u32 ;
struct ingenic_ecc_params {int size; int bytes; int strength; } ;
struct ingenic_ecc {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ BCH_BHCNT ; 
 int BCH_BHCNT_BLOCKSIZE_SHIFT ; 
 int BCH_BHCNT_PARITYSIZE_SHIFT ; 
 scalar_t__ BCH_BHCR ; 
 int BCH_BHCR_BCHE ; 
 int BCH_BHCR_BSEL_SHIFT ; 
 int BCH_BHCR_ENCE ; 
 int BCH_BHCR_INIT ; 
 scalar_t__ BCH_BHINT ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void jz4780_bch_reset(struct ingenic_ecc *bch,
			     struct ingenic_ecc_params *params, bool encode)
{
	u32 reg;

	/* Clear interrupt status. */
	writel(readl(bch->base + BCH_BHINT), bch->base + BCH_BHINT);

	/* Set up BCH count register. */
	reg = params->size << BCH_BHCNT_BLOCKSIZE_SHIFT;
	reg |= params->bytes << BCH_BHCNT_PARITYSIZE_SHIFT;
	writel(reg, bch->base + BCH_BHCNT);

	/* Initialise and enable BCH. */
	reg = BCH_BHCR_BCHE | BCH_BHCR_INIT;
	reg |= params->strength << BCH_BHCR_BSEL_SHIFT;
	if (encode)
		reg |= BCH_BHCR_ENCE;
	writel(reg, bch->base + BCH_BHCR);
}