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
struct TYPE_2__ {unsigned long long vtcr; int /*<<< orphan*/  vttbr; } ;
struct io_pgtable_cfg {int quirks; int oas; unsigned long long ias; TYPE_1__ arm_lpae_s2_cfg; } ;
struct io_pgtable {int dummy; } ;
struct arm_lpae_io_pgtable {scalar_t__ levels; unsigned long pgd_size; unsigned long pg_shift; struct io_pgtable iop; int /*<<< orphan*/  pgd; } ;
typedef  int /*<<< orphan*/  arm_lpae_iopte ;

/* Variables and functions */
 unsigned long long ARM_64_LPAE_S2_TCR_RES1 ; 
 int ARM_LPAE_GRANULE (struct arm_lpae_io_pgtable*) ; 
 scalar_t__ ARM_LPAE_MAX_LEVELS ; 
 unsigned long ARM_LPAE_S2_MAX_CONCAT_PAGES ; 
 unsigned long long ARM_LPAE_START_LVL (struct arm_lpae_io_pgtable*) ; 
 unsigned long long ARM_LPAE_TCR_IRGN0_SHIFT ; 
 unsigned long long ARM_LPAE_TCR_ORGN0_SHIFT ; 
 unsigned long long ARM_LPAE_TCR_PS_32_BIT ; 
 unsigned long long ARM_LPAE_TCR_PS_36_BIT ; 
 unsigned long long ARM_LPAE_TCR_PS_40_BIT ; 
 unsigned long long ARM_LPAE_TCR_PS_42_BIT ; 
 unsigned long long ARM_LPAE_TCR_PS_44_BIT ; 
 unsigned long long ARM_LPAE_TCR_PS_48_BIT ; 
 unsigned long long ARM_LPAE_TCR_PS_52_BIT ; 
 unsigned long long ARM_LPAE_TCR_PS_SHIFT ; 
 unsigned long long ARM_LPAE_TCR_RGN_WBWA ; 
 unsigned long long ARM_LPAE_TCR_SH0_SHIFT ; 
 unsigned long long ARM_LPAE_TCR_SH_IS ; 
 unsigned long long ARM_LPAE_TCR_SL0_MASK ; 
 unsigned long long ARM_LPAE_TCR_SL0_SHIFT ; 
 unsigned long long ARM_LPAE_TCR_T0SZ_SHIFT ; 
 unsigned long long ARM_LPAE_TCR_TG0_16K ; 
 unsigned long long ARM_LPAE_TCR_TG0_4K ; 
 unsigned long long ARM_LPAE_TCR_TG0_64K ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IO_PGTABLE_QUIRK_NON_STRICT ; 
#define  SZ_16K 130 
#define  SZ_4K 129 
#define  SZ_64K 128 
 int /*<<< orphan*/  __arm_lpae_alloc_pages (unsigned long,int /*<<< orphan*/ ,struct io_pgtable_cfg*) ; 
 struct arm_lpae_io_pgtable* arm_lpae_alloc_pgtable (struct io_pgtable_cfg*) ; 
 unsigned long ilog2 (int) ; 
 int /*<<< orphan*/  kfree (struct arm_lpae_io_pgtable*) ; 
 int /*<<< orphan*/  virt_to_phys (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static struct io_pgtable *
arm_64_lpae_alloc_pgtable_s2(struct io_pgtable_cfg *cfg, void *cookie)
{
	u64 reg, sl;
	struct arm_lpae_io_pgtable *data;

	/* The NS quirk doesn't apply at stage 2 */
	if (cfg->quirks & ~(IO_PGTABLE_QUIRK_NON_STRICT))
		return NULL;

	data = arm_lpae_alloc_pgtable(cfg);
	if (!data)
		return NULL;

	/*
	 * Concatenate PGDs at level 1 if possible in order to reduce
	 * the depth of the stage-2 walk.
	 */
	if (data->levels == ARM_LPAE_MAX_LEVELS) {
		unsigned long pgd_pages;

		pgd_pages = data->pgd_size >> ilog2(sizeof(arm_lpae_iopte));
		if (pgd_pages <= ARM_LPAE_S2_MAX_CONCAT_PAGES) {
			data->pgd_size = pgd_pages << data->pg_shift;
			data->levels--;
		}
	}

	/* VTCR */
	reg = ARM_64_LPAE_S2_TCR_RES1 |
	     (ARM_LPAE_TCR_SH_IS << ARM_LPAE_TCR_SH0_SHIFT) |
	     (ARM_LPAE_TCR_RGN_WBWA << ARM_LPAE_TCR_IRGN0_SHIFT) |
	     (ARM_LPAE_TCR_RGN_WBWA << ARM_LPAE_TCR_ORGN0_SHIFT);

	sl = ARM_LPAE_START_LVL(data);

	switch (ARM_LPAE_GRANULE(data)) {
	case SZ_4K:
		reg |= ARM_LPAE_TCR_TG0_4K;
		sl++; /* SL0 format is different for 4K granule size */
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
		reg |= (ARM_LPAE_TCR_PS_32_BIT << ARM_LPAE_TCR_PS_SHIFT);
		break;
	case 36:
		reg |= (ARM_LPAE_TCR_PS_36_BIT << ARM_LPAE_TCR_PS_SHIFT);
		break;
	case 40:
		reg |= (ARM_LPAE_TCR_PS_40_BIT << ARM_LPAE_TCR_PS_SHIFT);
		break;
	case 42:
		reg |= (ARM_LPAE_TCR_PS_42_BIT << ARM_LPAE_TCR_PS_SHIFT);
		break;
	case 44:
		reg |= (ARM_LPAE_TCR_PS_44_BIT << ARM_LPAE_TCR_PS_SHIFT);
		break;
	case 48:
		reg |= (ARM_LPAE_TCR_PS_48_BIT << ARM_LPAE_TCR_PS_SHIFT);
		break;
	case 52:
		reg |= (ARM_LPAE_TCR_PS_52_BIT << ARM_LPAE_TCR_PS_SHIFT);
		break;
	default:
		goto out_free_data;
	}

	reg |= (64ULL - cfg->ias) << ARM_LPAE_TCR_T0SZ_SHIFT;
	reg |= (~sl & ARM_LPAE_TCR_SL0_MASK) << ARM_LPAE_TCR_SL0_SHIFT;
	cfg->arm_lpae_s2_cfg.vtcr = reg;

	/* Allocate pgd pages */
	data->pgd = __arm_lpae_alloc_pages(data->pgd_size, GFP_KERNEL, cfg);
	if (!data->pgd)
		goto out_free_data;

	/* Ensure the empty pgd is visible before any actual TTBR write */
	wmb();

	/* VTTBR */
	cfg->arm_lpae_s2_cfg.vttbr = virt_to_phys(data->pgd);
	return &data->iop;

out_free_data:
	kfree(data);
	return NULL;
}