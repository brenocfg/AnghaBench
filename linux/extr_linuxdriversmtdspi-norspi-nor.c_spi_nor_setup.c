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
typedef  int u32 ;
struct spi_nor_hwcaps {int mask; } ;
struct TYPE_2__ {int mask; } ;
struct spi_nor_flash_parameter {int /*<<< orphan*/ * quad_enable; TYPE_1__ hwcaps; } ;
struct spi_nor {int /*<<< orphan*/ * quad_enable; int /*<<< orphan*/  write_proto; int /*<<< orphan*/  read_proto; int /*<<< orphan*/  dev; } ;
struct flash_info {int dummy; } ;

/* Variables and functions */
 int SNOR_HWCAPS_PP_4_4_4 ; 
 int SNOR_HWCAPS_PP_8_8_8 ; 
 int SNOR_HWCAPS_READ_2_2_2 ; 
 int SNOR_HWCAPS_READ_4_4_4 ; 
 int SNOR_HWCAPS_READ_8_8_8 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int spi_nor_get_protocol_width (int /*<<< orphan*/ ) ; 
 int spi_nor_select_erase (struct spi_nor*,struct flash_info const*) ; 
 int spi_nor_select_pp (struct spi_nor*,struct spi_nor_flash_parameter const*,int) ; 
 int spi_nor_select_read (struct spi_nor*,struct spi_nor_flash_parameter const*,int) ; 

__attribute__((used)) static int spi_nor_setup(struct spi_nor *nor, const struct flash_info *info,
			 const struct spi_nor_flash_parameter *params,
			 const struct spi_nor_hwcaps *hwcaps)
{
	u32 ignored_mask, shared_mask;
	bool enable_quad_io;
	int err;

	/*
	 * Keep only the hardware capabilities supported by both the SPI
	 * controller and the SPI flash memory.
	 */
	shared_mask = hwcaps->mask & params->hwcaps.mask;

	/* SPI n-n-n protocols are not supported yet. */
	ignored_mask = (SNOR_HWCAPS_READ_2_2_2 |
			SNOR_HWCAPS_READ_4_4_4 |
			SNOR_HWCAPS_READ_8_8_8 |
			SNOR_HWCAPS_PP_4_4_4 |
			SNOR_HWCAPS_PP_8_8_8);
	if (shared_mask & ignored_mask) {
		dev_dbg(nor->dev,
			"SPI n-n-n protocols are not supported yet.\n");
		shared_mask &= ~ignored_mask;
	}

	/* Select the (Fast) Read command. */
	err = spi_nor_select_read(nor, params, shared_mask);
	if (err) {
		dev_err(nor->dev,
			"can't select read settings supported by both the SPI controller and memory.\n");
		return err;
	}

	/* Select the Page Program command. */
	err = spi_nor_select_pp(nor, params, shared_mask);
	if (err) {
		dev_err(nor->dev,
			"can't select write settings supported by both the SPI controller and memory.\n");
		return err;
	}

	/* Select the Sector Erase command. */
	err = spi_nor_select_erase(nor, info);
	if (err) {
		dev_err(nor->dev,
			"can't select erase settings supported by both the SPI controller and memory.\n");
		return err;
	}

	/* Enable Quad I/O if needed. */
	enable_quad_io = (spi_nor_get_protocol_width(nor->read_proto) == 4 ||
			  spi_nor_get_protocol_width(nor->write_proto) == 4);
	if (enable_quad_io && params->quad_enable)
		nor->quad_enable = params->quad_enable;
	else
		nor->quad_enable = NULL;

	return 0;
}