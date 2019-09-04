#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int mask; } ;
struct spi_nor_flash_parameter {int size; scalar_t__ quad_enable; TYPE_1__ hwcaps; int /*<<< orphan*/ * page_programs; int /*<<< orphan*/ * reads; int /*<<< orphan*/  page_size; } ;
struct TYPE_4__ {scalar_t__ erasesize; } ;
struct spi_nor {TYPE_2__ mtd; scalar_t__ addr_width; } ;
struct flash_info {int sector_size; int n_sectors; int flags; scalar_t__ quad_enable; int /*<<< orphan*/  page_size; } ;
typedef  int /*<<< orphan*/  sfdp_params ;

/* Variables and functions */
 int JEDEC_MFR (struct flash_info const*) ; 
 size_t SNOR_CMD_PP ; 
 size_t SNOR_CMD_READ ; 
 size_t SNOR_CMD_READ_1_1_2 ; 
 size_t SNOR_CMD_READ_1_1_4 ; 
 size_t SNOR_CMD_READ_FAST ; 
 int SNOR_HWCAPS_PP ; 
 int SNOR_HWCAPS_PP_QUAD ; 
 int SNOR_HWCAPS_READ ; 
 int SNOR_HWCAPS_READ_1_1_2 ; 
 int SNOR_HWCAPS_READ_1_1_4 ; 
 int SNOR_HWCAPS_READ_FAST ; 
 int SNOR_HWCAPS_READ_QUAD ; 
#define  SNOR_MFR_MACRONIX 129 
#define  SNOR_MFR_MICRON 128 
 int /*<<< orphan*/  SNOR_PROTO_1_1_1 ; 
 int /*<<< orphan*/  SNOR_PROTO_1_1_2 ; 
 int /*<<< orphan*/  SNOR_PROTO_1_1_4 ; 
 int /*<<< orphan*/  SPINOR_OP_PP ; 
 int /*<<< orphan*/  SPINOR_OP_READ ; 
 int /*<<< orphan*/  SPINOR_OP_READ_1_1_2 ; 
 int /*<<< orphan*/  SPINOR_OP_READ_1_1_4 ; 
 int /*<<< orphan*/  SPINOR_OP_READ_FAST ; 
 int SPI_NOR_DUAL_READ ; 
 int SPI_NOR_NO_FR ; 
 int SPI_NOR_QUAD_READ ; 
 int SPI_NOR_SKIP_SFDP ; 
 scalar_t__ macronix_quad_enable ; 
 int /*<<< orphan*/  memcpy (struct spi_nor_flash_parameter*,struct spi_nor_flash_parameter*,int) ; 
 int /*<<< orphan*/  memset (struct spi_nor_flash_parameter*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ spansion_quad_enable ; 
 scalar_t__ spi_nor_parse_sfdp (struct spi_nor*,struct spi_nor_flash_parameter*) ; 
 int /*<<< orphan*/  spi_nor_set_pp_settings (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_nor_set_read_settings (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int spi_nor_init_params(struct spi_nor *nor,
			       const struct flash_info *info,
			       struct spi_nor_flash_parameter *params)
{
	/* Set legacy flash parameters as default. */
	memset(params, 0, sizeof(*params));

	/* Set SPI NOR sizes. */
	params->size = info->sector_size * info->n_sectors;
	params->page_size = info->page_size;

	/* (Fast) Read settings. */
	params->hwcaps.mask |= SNOR_HWCAPS_READ;
	spi_nor_set_read_settings(&params->reads[SNOR_CMD_READ],
				  0, 0, SPINOR_OP_READ,
				  SNOR_PROTO_1_1_1);

	if (!(info->flags & SPI_NOR_NO_FR)) {
		params->hwcaps.mask |= SNOR_HWCAPS_READ_FAST;
		spi_nor_set_read_settings(&params->reads[SNOR_CMD_READ_FAST],
					  0, 8, SPINOR_OP_READ_FAST,
					  SNOR_PROTO_1_1_1);
	}

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

	/* Page Program settings. */
	params->hwcaps.mask |= SNOR_HWCAPS_PP;
	spi_nor_set_pp_settings(&params->page_programs[SNOR_CMD_PP],
				SPINOR_OP_PP, SNOR_PROTO_1_1_1);

	/* Select the procedure to set the Quad Enable bit. */
	if (params->hwcaps.mask & (SNOR_HWCAPS_READ_QUAD |
				   SNOR_HWCAPS_PP_QUAD)) {
		switch (JEDEC_MFR(info)) {
		case SNOR_MFR_MACRONIX:
			params->quad_enable = macronix_quad_enable;
			break;

		case SNOR_MFR_MICRON:
			break;

		default:
			/* Kept only for backward compatibility purpose. */
			params->quad_enable = spansion_quad_enable;
			break;
		}

		/*
		 * Some manufacturer like GigaDevice may use different
		 * bit to set QE on different memories, so the MFR can't
		 * indicate the quad_enable method for this case, we need
		 * set it in flash info list.
		 */
		if (info->quad_enable)
			params->quad_enable = info->quad_enable;
	}

	/* Override the parameters with data read from SFDP tables. */
	nor->addr_width = 0;
	nor->mtd.erasesize = 0;
	if ((info->flags & (SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ)) &&
	    !(info->flags & SPI_NOR_SKIP_SFDP)) {
		struct spi_nor_flash_parameter sfdp_params;

		memcpy(&sfdp_params, params, sizeof(sfdp_params));
		if (spi_nor_parse_sfdp(nor, &sfdp_params)) {
			nor->addr_width = 0;
			nor->mtd.erasesize = 0;
		} else {
			memcpy(params, &sfdp_params, sizeof(*params));
		}
	}

	return 0;
}