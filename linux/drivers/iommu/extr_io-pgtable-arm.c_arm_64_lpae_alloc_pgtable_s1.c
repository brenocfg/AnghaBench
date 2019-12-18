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
typedef  unsigned long long u64 ;
struct TYPE_2__ {unsigned long long tcr; unsigned long long* mair; int /*<<< orphan*/ * ttbr; } ;
struct io_pgtable_cfg {int quirks; int oas; unsigned long long ias; TYPE_1__ arm_lpae_s1_cfg; scalar_t__ coherent_walk; } ;
struct io_pgtable {int dummy; } ;
struct arm_lpae_io_pgtable {struct io_pgtable iop; int /*<<< orphan*/  pgd; int /*<<< orphan*/  pgd_size; } ;

/* Variables and functions */
 int ARM_LPAE_GRANULE (struct arm_lpae_io_pgtable*) ; 
 unsigned long long ARM_LPAE_MAIR_ATTR_DEVICE ; 
 int /*<<< orphan*/  ARM_LPAE_MAIR_ATTR_IDX_CACHE ; 
 int /*<<< orphan*/  ARM_LPAE_MAIR_ATTR_IDX_DEV ; 
 int /*<<< orphan*/  ARM_LPAE_MAIR_ATTR_IDX_INC_OCACHE ; 
 int /*<<< orphan*/  ARM_LPAE_MAIR_ATTR_IDX_NC ; 
 unsigned long long ARM_LPAE_MAIR_ATTR_INC_OWBRWA ; 
 unsigned long long ARM_LPAE_MAIR_ATTR_NC ; 
 unsigned long long ARM_LPAE_MAIR_ATTR_SHIFT (int /*<<< orphan*/ ) ; 
 unsigned long long ARM_LPAE_MAIR_ATTR_WBRWA ; 
 unsigned long long ARM_LPAE_TCR_EPD1 ; 
 unsigned long long ARM_LPAE_TCR_IPS_SHIFT ; 
 unsigned long long ARM_LPAE_TCR_IRGN0_SHIFT ; 
 unsigned long long ARM_LPAE_TCR_ORGN0_SHIFT ; 
 unsigned long long ARM_LPAE_TCR_PS_32_BIT ; 
 unsigned long long ARM_LPAE_TCR_PS_36_BIT ; 
 unsigned long long ARM_LPAE_TCR_PS_40_BIT ; 
 unsigned long long ARM_LPAE_TCR_PS_42_BIT ; 
 unsigned long long ARM_LPAE_TCR_PS_44_BIT ; 
 unsigned long long ARM_LPAE_TCR_PS_48_BIT ; 
 unsigned long long ARM_LPAE_TCR_PS_52_BIT ; 
 unsigned long long ARM_LPAE_TCR_RGN_NC ; 
 unsigned long long ARM_LPAE_TCR_RGN_WBWA ; 
 unsigned long long ARM_LPAE_TCR_SH0_SHIFT ; 
 unsigned long long ARM_LPAE_TCR_SH_IS ; 
 unsigned long long ARM_LPAE_TCR_SH_OS ; 
 unsigned long long ARM_LPAE_TCR_T0SZ_SHIFT ; 
 unsigned long long ARM_LPAE_TCR_TG0_16K ; 
 unsigned long long ARM_LPAE_TCR_TG0_4K ; 
 unsigned long long ARM_LPAE_TCR_TG0_64K ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IO_PGTABLE_QUIRK_ARM_NS ; 
 int IO_PGTABLE_QUIRK_NON_STRICT ; 
#define  SZ_16K 130 
#define  SZ_4K 129 
#define  SZ_64K 128 
 int /*<<< orphan*/  __arm_lpae_alloc_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct io_pgtable_cfg*) ; 
 struct arm_lpae_io_pgtable* arm_lpae_alloc_pgtable (struct io_pgtable_cfg*) ; 
 int /*<<< orphan*/  kfree (struct arm_lpae_io_pgtable*) ; 
 int /*<<< orphan*/  virt_to_phys (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static struct io_pgtable *
arm_64_lpae_alloc_pgtable_s1(struct io_pgtable_cfg *cfg, void *cookie)
{
	u64 reg;
	struct arm_lpae_io_pgtable *data;

	if (cfg->quirks & ~(IO_PGTABLE_QUIRK_ARM_NS |
			    IO_PGTABLE_QUIRK_NON_STRICT))
		return NULL;

	data = arm_lpae_alloc_pgtable(cfg);
	if (!data)
		return NULL;

	/* TCR */
	if (cfg->coherent_walk) {
		reg = (ARM_LPAE_TCR_SH_IS << ARM_LPAE_TCR_SH0_SHIFT) |
		      (ARM_LPAE_TCR_RGN_WBWA << ARM_LPAE_TCR_IRGN0_SHIFT) |
		      (ARM_LPAE_TCR_RGN_WBWA << ARM_LPAE_TCR_ORGN0_SHIFT);
	} else {
		reg = (ARM_LPAE_TCR_SH_OS << ARM_LPAE_TCR_SH0_SHIFT) |
		      (ARM_LPAE_TCR_RGN_NC << ARM_LPAE_TCR_IRGN0_SHIFT) |
		      (ARM_LPAE_TCR_RGN_NC << ARM_LPAE_TCR_ORGN0_SHIFT);
	}

	switch (ARM_LPAE_GRANULE(data)) {
	case SZ_4K:
		reg |= ARM_LPAE_TCR_TG0_4K;
		break;
	case SZ_16K:
		reg |= ARM_LPAE_TCR_TG0_16K;
		break;
	case SZ_64K:
		reg |= ARM_LPAE_TCR_TG0_64K;
		break;
	}

	switch (cfg->oas) {
	case 32:
		reg |= (ARM_LPAE_TCR_PS_32_BIT << ARM_LPAE_TCR_IPS_SHIFT);
		break;
	case 36:
		reg |= (ARM_LPAE_TCR_PS_36_BIT << ARM_LPAE_TCR_IPS_SHIFT);
		break;
	case 40:
		reg |= (ARM_LPAE_TCR_PS_40_BIT << ARM_LPAE_TCR_IPS_SHIFT);
		break;
	case 42:
		reg |= (ARM_LPAE_TCR_PS_42_BIT << ARM_LPAE_TCR_IPS_SHIFT);
		break;
	case 44:
		reg |= (ARM_LPAE_TCR_PS_44_BIT << ARM_LPAE_TCR_IPS_SHIFT);
		break;
	case 48:
		reg |= (ARM_LPAE_TCR_PS_48_BIT << ARM_LPAE_TCR_IPS_SHIFT);
		break;
	case 52:
		reg |= (ARM_LPAE_TCR_PS_52_BIT << ARM_LPAE_TCR_IPS_SHIFT);
		break;
	default:
		goto out_free_data;
	}

	reg |= (64ULL - cfg->ias) << ARM_LPAE_TCR_T0SZ_SHIFT;

	/* Disable speculative walks through TTBR1 */
	reg |= ARM_LPAE_TCR_EPD1;
	cfg->arm_lpae_s1_cfg.tcr = reg;

	/* MAIRs */
	reg = (ARM_LPAE_MAIR_ATTR_NC
	       << ARM_LPAE_MAIR_ATTR_SHIFT(ARM_LPAE_MAIR_ATTR_IDX_NC)) |
	      (ARM_LPAE_MAIR_ATTR_WBRWA
	       << ARM_LPAE_MAIR_ATTR_SHIFT(ARM_LPAE_MAIR_ATTR_IDX_CACHE)) |
	      (ARM_LPAE_MAIR_ATTR_DEVICE
	       << ARM_LPAE_MAIR_ATTR_SHIFT(ARM_LPAE_MAIR_ATTR_IDX_DEV)) |
	      (ARM_LPAE_MAIR_ATTR_INC_OWBRWA
	       << ARM_LPAE_MAIR_ATTR_SHIFT(ARM_LPAE_MAIR_ATTR_IDX_INC_OCACHE));

	cfg->arm_lpae_s1_cfg.mair[0] = reg;
	cfg->arm_lpae_s1_cfg.mair[1] = 0;

	/* Looking good; allocate a pgd */
	data->pgd = __arm_lpae_alloc_pages(data->pgd_size, GFP_KERNEL, cfg);
	if (!data->pgd)
		goto out_free_data;

	/* Ensure the empty pgd is visible before any actual TTBR write */
	wmb();

	/* TTBRs */
	cfg->arm_lpae_s1_cfg.ttbr[0] = virt_to_phys(data->pgd);
	cfg->arm_lpae_s1_cfg.ttbr[1] = 0;
	return &data->iop;

out_free_data:
	kfree(data);
	return NULL;
}