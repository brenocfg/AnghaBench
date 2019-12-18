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
struct brcmnand_controller {int nand_version; int reg_spacing; int max_page_size; int max_block_size; unsigned int const* page_sizes; unsigned int const* block_sizes; int max_oob; int /*<<< orphan*/  features; TYPE_1__* dev; int /*<<< orphan*/  cs0_offsets; int /*<<< orphan*/  cs_offsets; int /*<<< orphan*/  reg_offsets; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMNAND_HAS_1K_SECTORS ; 
 int /*<<< orphan*/  BRCMNAND_HAS_CACHE_MODE ; 
 int /*<<< orphan*/  BRCMNAND_HAS_PREFETCH ; 
 int /*<<< orphan*/  BRCMNAND_HAS_WP ; 
 int ENODEV ; 
 int /*<<< orphan*/  brcmnand_cs_offsets ; 
 int /*<<< orphan*/  brcmnand_cs_offsets_cs0 ; 
 int /*<<< orphan*/  brcmnand_cs_offsets_v71 ; 
 int /*<<< orphan*/  brcmnand_regs_v40 ; 
 int /*<<< orphan*/  brcmnand_regs_v50 ; 
 int /*<<< orphan*/  brcmnand_regs_v60 ; 
 int /*<<< orphan*/  brcmnand_regs_v71 ; 
 int /*<<< orphan*/  brcmnand_regs_v72 ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,int) ; 
 int nand_readreg (struct brcmnand_controller*,int /*<<< orphan*/ ) ; 
 scalar_t__ of_property_read_bool (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int brcmnand_revision_init(struct brcmnand_controller *ctrl)
{
	static const unsigned int block_sizes_v6[] = { 8, 16, 128, 256, 512, 1024, 2048, 0 };
	static const unsigned int block_sizes_v4[] = { 16, 128, 8, 512, 256, 1024, 2048, 0 };
	static const unsigned int page_sizes[] = { 512, 2048, 4096, 8192, 0 };

	ctrl->nand_version = nand_readreg(ctrl, 0) & 0xffff;

	/* Only support v4.0+? */
	if (ctrl->nand_version < 0x0400) {
		dev_err(ctrl->dev, "version %#x not supported\n",
			ctrl->nand_version);
		return -ENODEV;
	}

	/* Register offsets */
	if (ctrl->nand_version >= 0x0702)
		ctrl->reg_offsets = brcmnand_regs_v72;
	else if (ctrl->nand_version == 0x0701)
		ctrl->reg_offsets = brcmnand_regs_v71;
	else if (ctrl->nand_version >= 0x0600)
		ctrl->reg_offsets = brcmnand_regs_v60;
	else if (ctrl->nand_version >= 0x0500)
		ctrl->reg_offsets = brcmnand_regs_v50;
	else if (ctrl->nand_version >= 0x0400)
		ctrl->reg_offsets = brcmnand_regs_v40;

	/* Chip-select stride */
	if (ctrl->nand_version >= 0x0701)
		ctrl->reg_spacing = 0x14;
	else
		ctrl->reg_spacing = 0x10;

	/* Per chip-select registers */
	if (ctrl->nand_version >= 0x0701) {
		ctrl->cs_offsets = brcmnand_cs_offsets_v71;
	} else {
		ctrl->cs_offsets = brcmnand_cs_offsets;

		/* v5.0 and earlier has a different CS0 offset layout */
		if (ctrl->nand_version <= 0x0500)
			ctrl->cs0_offsets = brcmnand_cs_offsets_cs0;
	}

	/* Page / block sizes */
	if (ctrl->nand_version >= 0x0701) {
		/* >= v7.1 use nice power-of-2 values! */
		ctrl->max_page_size = 16 * 1024;
		ctrl->max_block_size = 2 * 1024 * 1024;
	} else {
		ctrl->page_sizes = page_sizes;
		if (ctrl->nand_version >= 0x0600)
			ctrl->block_sizes = block_sizes_v6;
		else
			ctrl->block_sizes = block_sizes_v4;

		if (ctrl->nand_version < 0x0400) {
			ctrl->max_page_size = 4096;
			ctrl->max_block_size = 512 * 1024;
		}
	}

	/* Maximum spare area sector size (per 512B) */
	if (ctrl->nand_version == 0x0702)
		ctrl->max_oob = 128;
	else if (ctrl->nand_version >= 0x0600)
		ctrl->max_oob = 64;
	else if (ctrl->nand_version >= 0x0500)
		ctrl->max_oob = 32;
	else
		ctrl->max_oob = 16;

	/* v6.0 and newer (except v6.1) have prefetch support */
	if (ctrl->nand_version >= 0x0600 && ctrl->nand_version != 0x0601)
		ctrl->features |= BRCMNAND_HAS_PREFETCH;

	/*
	 * v6.x has cache mode, but it's implemented differently. Ignore it for
	 * now.
	 */
	if (ctrl->nand_version >= 0x0700)
		ctrl->features |= BRCMNAND_HAS_CACHE_MODE;

	if (ctrl->nand_version >= 0x0500)
		ctrl->features |= BRCMNAND_HAS_1K_SECTORS;

	if (ctrl->nand_version >= 0x0700)
		ctrl->features |= BRCMNAND_HAS_WP;
	else if (of_property_read_bool(ctrl->dev->of_node, "brcm,nand-has-wp"))
		ctrl->features |= BRCMNAND_HAS_WP;

	return 0;
}