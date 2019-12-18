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
typedef  size_t u8 ;
typedef  int u64 ;
struct TYPE_2__ {int mask; } ;
struct spi_nor_erase_map {int /*<<< orphan*/ * erase_type; } ;
struct spi_nor_flash_parameter {int size; int /*<<< orphan*/ * page_programs; TYPE_1__ hwcaps; int /*<<< orphan*/ * reads; int /*<<< orphan*/  page_size; int /*<<< orphan*/  setup; int /*<<< orphan*/  set_4byte; int /*<<< orphan*/  quad_enable; struct spi_nor_erase_map erase_map; } ;
struct spi_nor {struct flash_info* info; struct spi_nor_flash_parameter params; } ;
struct flash_info {unsigned int sector_size; int n_sectors; int flags; int /*<<< orphan*/  page_size; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 size_t BIT (size_t) ; 
 int SECT_4K ; 
 int SECT_4K_PMC ; 
 size_t SNOR_CMD_PP ; 
 size_t SNOR_CMD_READ ; 
 size_t SNOR_CMD_READ_1_1_2 ; 
 size_t SNOR_CMD_READ_1_1_4 ; 
 size_t SNOR_CMD_READ_1_1_8 ; 
 size_t SNOR_CMD_READ_FAST ; 
 int SNOR_HWCAPS_PP ; 
 int SNOR_HWCAPS_READ ; 
 int SNOR_HWCAPS_READ_1_1_2 ; 
 int SNOR_HWCAPS_READ_1_1_4 ; 
 int SNOR_HWCAPS_READ_1_1_8 ; 
 int SNOR_HWCAPS_READ_FAST ; 
 int /*<<< orphan*/  SNOR_PROTO_1_1_1 ; 
 int /*<<< orphan*/  SNOR_PROTO_1_1_2 ; 
 int /*<<< orphan*/  SNOR_PROTO_1_1_4 ; 
 int /*<<< orphan*/  SNOR_PROTO_1_1_8 ; 
 int /*<<< orphan*/  SPINOR_OP_BE_4K ; 
 int /*<<< orphan*/  SPINOR_OP_BE_4K_PMC ; 
 int /*<<< orphan*/  SPINOR_OP_PP ; 
 int /*<<< orphan*/  SPINOR_OP_READ ; 
 int /*<<< orphan*/  SPINOR_OP_READ_1_1_2 ; 
 int /*<<< orphan*/  SPINOR_OP_READ_1_1_4 ; 
 int /*<<< orphan*/  SPINOR_OP_READ_1_1_8 ; 
 int /*<<< orphan*/  SPINOR_OP_READ_FAST ; 
 int /*<<< orphan*/  SPINOR_OP_SE ; 
 int SPI_NOR_DUAL_READ ; 
 int SPI_NOR_NO_FR ; 
 int SPI_NOR_OCTAL_READ ; 
 int SPI_NOR_QUAD_READ ; 
 int /*<<< orphan*/  of_property_read_bool (struct device_node*,char*) ; 
 int /*<<< orphan*/  spansion_quad_enable ; 
 int /*<<< orphan*/  spansion_set_4byte ; 
 int /*<<< orphan*/  spi_nor_default_setup ; 
 struct device_node* spi_nor_get_flash_node (struct spi_nor*) ; 
 int /*<<< orphan*/  spi_nor_init_uniform_erase_map (struct spi_nor_erase_map*,size_t,int) ; 
 int /*<<< orphan*/  spi_nor_set_erase_type (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_nor_set_pp_settings (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_nor_set_read_settings (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void spi_nor_info_init_params(struct spi_nor *nor)
{
	struct spi_nor_flash_parameter *params = &nor->params;
	struct spi_nor_erase_map *map = &params->erase_map;
	const struct flash_info *info = nor->info;
	struct device_node *np = spi_nor_get_flash_node(nor);
	u8 i, erase_mask;

	/* Initialize legacy flash parameters and settings. */
	params->quad_enable = spansion_quad_enable;
	params->set_4byte = spansion_set_4byte;
	params->setup = spi_nor_default_setup;

	/* Set SPI NOR sizes. */
	params->size = (u64)info->sector_size * info->n_sectors;
	params->page_size = info->page_size;

	if (!(info->flags & SPI_NOR_NO_FR)) {
		/* Default to Fast Read for DT and non-DT platform devices. */
		params->hwcaps.mask |= SNOR_HWCAPS_READ_FAST;

		/* Mask out Fast Read if not requested at DT instantiation. */
		if (np && !of_property_read_bool(np, "m25p,fast-read"))
			params->hwcaps.mask &= ~SNOR_HWCAPS_READ_FAST;
	}

	/* (Fast) Read settings. */
	params->hwcaps.mask |= SNOR_HWCAPS_READ;
	spi_nor_set_read_settings(&params->reads[SNOR_CMD_READ],
				  0, 0, SPINOR_OP_READ,
				  SNOR_PROTO_1_1_1);

	if (params->hwcaps.mask & SNOR_HWCAPS_READ_FAST)
		spi_nor_set_read_settings(&params->reads[SNOR_CMD_READ_FAST],
					  0, 8, SPINOR_OP_READ_FAST,
					  SNOR_PROTO_1_1_1);

	if (info->flags & SPI_NOR_DUAL_READ) {
		params->hwcaps.mask |= SNOR_HWCAPS_READ_1_1_2;
		spi_nor_set_read_settings(&params->reads[SNOR_CMD_READ_1_1_2],
					  0, 8, SPINOR_OP_READ_1_1_2,
					  SNOR_PROTO_1_1_2);
	}

	if (info->flags & SPI_NOR_QUAD_READ) {
		params->hwcaps.mask |= SNOR_HWCAPS_READ_1_1_4;
		spi_nor_set_read_settings(&params->reads[SNOR_CMD_READ_1_1_4],
					  0, 8, SPINOR_OP_READ_1_1_4,
					  SNOR_PROTO_1_1_4);
	}

	if (info->flags & SPI_NOR_OCTAL_READ) {
		params->hwcaps.mask |= SNOR_HWCAPS_READ_1_1_8;
		spi_nor_set_read_settings(&params->reads[SNOR_CMD_READ_1_1_8],
					  0, 8, SPINOR_OP_READ_1_1_8,
					  SNOR_PROTO_1_1_8);
	}

	/* Page Program settings. */
	params->hwcaps.mask |= SNOR_HWCAPS_PP;
	spi_nor_set_pp_settings(&params->page_programs[SNOR_CMD_PP],
				SPINOR_OP_PP, SNOR_PROTO_1_1_1);

	/*
	 * Sector Erase settings. Sort Erase Types in ascending order, with the
	 * smallest erase size starting at BIT(0).
	 */
	erase_mask = 0;
	i = 0;
	if (info->flags & SECT_4K_PMC) {
		erase_mask |= BIT(i);
		spi_nor_set_erase_type(&map->erase_type[i], 4096u,
				       SPINOR_OP_BE_4K_PMC);
		i++;
	} else if (info->flags & SECT_4K) {
		erase_mask |= BIT(i);
		spi_nor_set_erase_type(&map->erase_type[i], 4096u,
				       SPINOR_OP_BE_4K);
		i++;
	}
	erase_mask |= BIT(i);
	spi_nor_set_erase_type(&map->erase_type[i], info->sector_size,
			       SPINOR_OP_SE);
	spi_nor_init_uniform_erase_map(map, erase_mask, params->size);
}