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
struct spi_nor_flash_parameter {TYPE_1__ hwcaps; } ;
struct spi_nor {int /*<<< orphan*/  dev; scalar_t__ spimem; struct spi_nor_flash_parameter params; } ;

/* Variables and functions */
 int SNOR_HWCAPS_X_X_X ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int spi_nor_select_erase (struct spi_nor*) ; 
 int spi_nor_select_pp (struct spi_nor*,int) ; 
 int spi_nor_select_read (struct spi_nor*,int) ; 
 int /*<<< orphan*/  spi_nor_spimem_adjust_hwcaps (struct spi_nor*,int*) ; 

__attribute__((used)) static int spi_nor_default_setup(struct spi_nor *nor,
				 const struct spi_nor_hwcaps *hwcaps)
{
	struct spi_nor_flash_parameter *params = &nor->params;
	u32 ignored_mask, shared_mask;
	int err;

	/*
	 * Keep only the hardware capabilities supported by both the SPI
	 * controller and the SPI flash memory.
	 */
	shared_mask = hwcaps->mask & params->hwcaps.mask;

	if (nor->spimem) {
		/*
		 * When called from spi_nor_probe(), all caps are set and we
		 * need to discard some of them based on what the SPI
		 * controller actually supports (using spi_mem_supports_op()).
		 */
		spi_nor_spimem_adjust_hwcaps(nor, &shared_mask);
	} else {
		/*
		 * SPI n-n-n protocols are not supported when the SPI
		 * controller directly implements the spi_nor interface.
		 * Yet another reason to switch to spi-mem.
		 */
		ignored_mask = SNOR_HWCAPS_X_X_X;
		if (shared_mask & ignored_mask) {
			dev_dbg(nor->dev,
				"SPI n-n-n protocols are not supported.\n");
			shared_mask &= ~ignored_mask;
		}
	}

	/* Select the (Fast) Read command. */
	err = spi_nor_select_read(nor, shared_mask);
	if (err) {
		dev_err(nor->dev,
			"can't select read settings supported by both the SPI controller and memory.\n");
		return err;
	}

	/* Select the Page Program command. */
	err = spi_nor_select_pp(nor, shared_mask);
	if (err) {
		dev_err(nor->dev,
			"can't select write settings supported by both the SPI controller and memory.\n");
		return err;
	}

	/* Select the Sector Erase command. */
	err = spi_nor_select_erase(nor);
	if (err) {
		dev_err(nor->dev,
			"can't select erase settings supported by both the SPI controller and memory.\n");
		return err;
	}

	return 0;
}