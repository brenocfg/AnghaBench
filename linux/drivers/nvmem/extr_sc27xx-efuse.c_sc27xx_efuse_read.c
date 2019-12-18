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
typedef  size_t u32 ;
struct sc27xx_efuse {int /*<<< orphan*/  regmap; scalar_t__ base; } ;

/* Variables and functions */
 size_t BITS_PER_BYTE ; 
 int EINVAL ; 
 scalar_t__ SC27XX_EFUSE_BLOCK_INDEX ; 
 size_t SC27XX_EFUSE_BLOCK_MASK ; 
 size_t SC27XX_EFUSE_BLOCK_MAX ; 
 size_t SC27XX_EFUSE_BLOCK_WIDTH ; 
 int /*<<< orphan*/  SC27XX_EFUSE_CLR_RDDONE ; 
 scalar_t__ SC27XX_EFUSE_DATA_RD ; 
 int /*<<< orphan*/  SC27XX_EFUSE_EN ; 
 scalar_t__ SC27XX_EFUSE_MODE_CTRL ; 
 int /*<<< orphan*/  SC27XX_EFUSE_RD_DONE ; 
 int /*<<< orphan*/  SC27XX_EFUSE_RD_START ; 
 int /*<<< orphan*/  SC27XX_EFUSE_STANDBY ; 
 scalar_t__ SC27XX_MODULE_EN ; 
 int /*<<< orphan*/  memcpy (void*,size_t*,size_t) ; 
 int regmap_read (int /*<<< orphan*/ ,scalar_t__,size_t*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regmap_write (int /*<<< orphan*/ ,scalar_t__,size_t) ; 
 int sc27xx_efuse_lock (struct sc27xx_efuse*) ; 
 int sc27xx_efuse_poll_status (struct sc27xx_efuse*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sc27xx_efuse_unlock (struct sc27xx_efuse*) ; 

__attribute__((used)) static int sc27xx_efuse_read(void *context, u32 offset, void *val, size_t bytes)
{
	struct sc27xx_efuse *efuse = context;
	u32 buf, blk_index = offset / SC27XX_EFUSE_BLOCK_WIDTH;
	u32 blk_offset = (offset % SC27XX_EFUSE_BLOCK_WIDTH) * BITS_PER_BYTE;
	int ret;

	if (blk_index > SC27XX_EFUSE_BLOCK_MAX ||
	    bytes > SC27XX_EFUSE_BLOCK_WIDTH)
		return -EINVAL;

	ret = sc27xx_efuse_lock(efuse);
	if (ret)
		return ret;

	/* Enable the efuse controller. */
	ret = regmap_update_bits(efuse->regmap, SC27XX_MODULE_EN,
				 SC27XX_EFUSE_EN, SC27XX_EFUSE_EN);
	if (ret)
		goto unlock_efuse;

	/*
	 * Before reading, we should ensure the efuse controller is in
	 * standby state.
	 */
	ret = sc27xx_efuse_poll_status(efuse, SC27XX_EFUSE_STANDBY);
	if (ret)
		goto disable_efuse;

	/* Set the block address to be read. */
	ret = regmap_write(efuse->regmap,
			   efuse->base + SC27XX_EFUSE_BLOCK_INDEX,
			   blk_index & SC27XX_EFUSE_BLOCK_MASK);
	if (ret)
		goto disable_efuse;

	/* Start reading process from efuse memory. */
	ret = regmap_update_bits(efuse->regmap,
				 efuse->base + SC27XX_EFUSE_MODE_CTRL,
				 SC27XX_EFUSE_RD_START,
				 SC27XX_EFUSE_RD_START);
	if (ret)
		goto disable_efuse;

	/*
	 * Polling the read done status to make sure the reading process
	 * is completed, that means the data can be read out now.
	 */
	ret = sc27xx_efuse_poll_status(efuse, SC27XX_EFUSE_RD_DONE);
	if (ret)
		goto disable_efuse;

	/* Read data from efuse memory. */
	ret = regmap_read(efuse->regmap, efuse->base + SC27XX_EFUSE_DATA_RD,
			  &buf);
	if (ret)
		goto disable_efuse;

	/* Clear the read done flag. */
	ret = regmap_update_bits(efuse->regmap,
				 efuse->base + SC27XX_EFUSE_MODE_CTRL,
				 SC27XX_EFUSE_CLR_RDDONE,
				 SC27XX_EFUSE_CLR_RDDONE);

disable_efuse:
	/* Disable the efuse controller after reading. */
	regmap_update_bits(efuse->regmap, SC27XX_MODULE_EN, SC27XX_EFUSE_EN, 0);
unlock_efuse:
	sc27xx_efuse_unlock(efuse);

	if (!ret) {
		buf >>= blk_offset;
		memcpy(val, &buf, bytes);
	}

	return ret;
}