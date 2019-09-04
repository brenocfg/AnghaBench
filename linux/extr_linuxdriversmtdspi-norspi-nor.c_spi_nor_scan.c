#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct spi_nor_hwcaps {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  mask; } ;
struct spi_nor_flash_parameter {int size; TYPE_3__ hwcaps; int /*<<< orphan*/  page_size; } ;
struct TYPE_5__ {struct device* parent; } ;
struct mtd_info {int writesize; int size; int erasesize; int numeraseregions; TYPE_1__* eraseregions; scalar_t__ name; int /*<<< orphan*/  writebufsize; TYPE_2__ dev; int /*<<< orphan*/  flags; int /*<<< orphan*/  _write; int /*<<< orphan*/  _is_locked; int /*<<< orphan*/  _unlock; int /*<<< orphan*/  _lock; int /*<<< orphan*/  _resume; int /*<<< orphan*/  _read; int /*<<< orphan*/  _erase; int /*<<< orphan*/  type; struct spi_nor* priv; } ;
struct spi_nor {int addr_width; struct flash_info const* info; int /*<<< orphan*/  flags; int /*<<< orphan*/  page_size; scalar_t__ flash_is_locked; scalar_t__ flash_unlock; scalar_t__ flash_lock; int /*<<< orphan*/  lock; void* write_proto; void* read_proto; void* reg_proto; struct mtd_info mtd; struct device* dev; } ;
struct flash_info {int flags; int addr_width; int /*<<< orphan*/  name; scalar_t__ id_len; } ;
struct device_node {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_4__ {int erasesize; int /*<<< orphan*/  numblocks; scalar_t__ offset; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 scalar_t__ IS_ERR (struct flash_info const*) ; 
 scalar_t__ IS_ERR_OR_NULL (struct flash_info const*) ; 
 scalar_t__ JEDEC_MFR (struct flash_info const*) ; 
 int /*<<< orphan*/  MTD_CAP_NORFLASH ; 
 int /*<<< orphan*/  MTD_NORFLASH ; 
 int /*<<< orphan*/  MTD_NO_ERASE ; 
 int NO_CHIP_ERASE ; 
 int PTR_ERR (struct flash_info const*) ; 
 int /*<<< orphan*/  SNOR_F_BROKEN_RESET ; 
 int /*<<< orphan*/  SNOR_F_HAS_SR_TB ; 
 int /*<<< orphan*/  SNOR_F_NO_OP_CHIP_ERASE ; 
 int /*<<< orphan*/  SNOR_F_READY_XSR_RDY ; 
 int /*<<< orphan*/  SNOR_F_USE_CLSR ; 
 int /*<<< orphan*/  SNOR_F_USE_FSR ; 
 int /*<<< orphan*/  SNOR_HWCAPS_READ_FAST ; 
 scalar_t__ SNOR_MFR_MICRON ; 
 scalar_t__ SNOR_MFR_SPANSION ; 
 void* SNOR_PROTO_1_1_1 ; 
 int SPI_NOR_4B_OPCODES ; 
 int SPI_NOR_HAS_LOCK ; 
 int SPI_NOR_HAS_TB ; 
 int SPI_NOR_MAX_ADDR_WIDTH ; 
 int SPI_NOR_NO_ERASE ; 
 int SPI_NOR_NO_FR ; 
 int SPI_S3AN ; 
 int SST_WRITE ; 
 int USE_CLSR ; 
 int USE_FSR ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int,long long,int,int,int,...) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ,long long) ; 
 scalar_t__ dev_name (struct device*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 scalar_t__ of_property_read_bool (struct device_node*,char*) ; 
 int s3an_nor_scan (struct flash_info const*,struct spi_nor*) ; 
 int spi_nor_check (struct spi_nor*) ; 
 int /*<<< orphan*/  spi_nor_erase ; 
 struct device_node* spi_nor_get_flash_node (struct spi_nor*) ; 
 int spi_nor_init (struct spi_nor*) ; 
 int spi_nor_init_params (struct spi_nor*,struct flash_info const*,struct spi_nor_flash_parameter*) ; 
 int /*<<< orphan*/  spi_nor_is_locked ; 
 int /*<<< orphan*/  spi_nor_lock ; 
 struct flash_info* spi_nor_match_id (char const*) ; 
 int /*<<< orphan*/  spi_nor_read ; 
 struct flash_info* spi_nor_read_id (struct spi_nor*) ; 
 int /*<<< orphan*/  spi_nor_resume ; 
 int /*<<< orphan*/  spi_nor_set_4byte_opcodes (struct spi_nor*,struct flash_info const*) ; 
 int spi_nor_setup (struct spi_nor*,struct flash_info const*,struct spi_nor_flash_parameter*,struct spi_nor_hwcaps const*) ; 
 int /*<<< orphan*/  spi_nor_unlock ; 
 int /*<<< orphan*/  spi_nor_write ; 
 int /*<<< orphan*/  sst_write ; 
 scalar_t__ stm_is_locked ; 
 scalar_t__ stm_lock ; 
 scalar_t__ stm_unlock ; 

int spi_nor_scan(struct spi_nor *nor, const char *name,
		 const struct spi_nor_hwcaps *hwcaps)
{
	struct spi_nor_flash_parameter params;
	const struct flash_info *info = NULL;
	struct device *dev = nor->dev;
	struct mtd_info *mtd = &nor->mtd;
	struct device_node *np = spi_nor_get_flash_node(nor);
	int ret;
	int i;

	ret = spi_nor_check(nor);
	if (ret)
		return ret;

	/* Reset SPI protocol for all commands. */
	nor->reg_proto = SNOR_PROTO_1_1_1;
	nor->read_proto = SNOR_PROTO_1_1_1;
	nor->write_proto = SNOR_PROTO_1_1_1;

	if (name)
		info = spi_nor_match_id(name);
	/* Try to auto-detect if chip name wasn't specified or not found */
	if (!info)
		info = spi_nor_read_id(nor);
	if (IS_ERR_OR_NULL(info))
		return -ENOENT;

	/*
	 * If caller has specified name of flash model that can normally be
	 * detected using JEDEC, let's verify it.
	 */
	if (name && info->id_len) {
		const struct flash_info *jinfo;

		jinfo = spi_nor_read_id(nor);
		if (IS_ERR(jinfo)) {
			return PTR_ERR(jinfo);
		} else if (jinfo != info) {
			/*
			 * JEDEC knows better, so overwrite platform ID. We
			 * can't trust partitions any longer, but we'll let
			 * mtd apply them anyway, since some partitions may be
			 * marked read-only, and we don't want to lose that
			 * information, even if it's not 100% accurate.
			 */
			dev_warn(dev, "found %s, expected %s\n",
				 jinfo->name, info->name);
			info = jinfo;
		}
	}

	mutex_init(&nor->lock);

	/*
	 * Make sure the XSR_RDY flag is set before calling
	 * spi_nor_wait_till_ready(). Xilinx S3AN share MFR
	 * with Atmel spi-nor
	 */
	if (info->flags & SPI_S3AN)
		nor->flags |=  SNOR_F_READY_XSR_RDY;

	/* Parse the Serial Flash Discoverable Parameters table. */
	ret = spi_nor_init_params(nor, info, &params);
	if (ret)
		return ret;

	if (!mtd->name)
		mtd->name = dev_name(dev);
	mtd->priv = nor;
	mtd->type = MTD_NORFLASH;
	mtd->writesize = 1;
	mtd->flags = MTD_CAP_NORFLASH;
	mtd->size = params.size;
	mtd->_erase = spi_nor_erase;
	mtd->_read = spi_nor_read;
	mtd->_resume = spi_nor_resume;

	/* NOR protection support for STmicro/Micron chips and similar */
	if (JEDEC_MFR(info) == SNOR_MFR_MICRON ||
			info->flags & SPI_NOR_HAS_LOCK) {
		nor->flash_lock = stm_lock;
		nor->flash_unlock = stm_unlock;
		nor->flash_is_locked = stm_is_locked;
	}

	if (nor->flash_lock && nor->flash_unlock && nor->flash_is_locked) {
		mtd->_lock = spi_nor_lock;
		mtd->_unlock = spi_nor_unlock;
		mtd->_is_locked = spi_nor_is_locked;
	}

	/* sst nor chips use AAI word program */
	if (info->flags & SST_WRITE)
		mtd->_write = sst_write;
	else
		mtd->_write = spi_nor_write;

	if (info->flags & USE_FSR)
		nor->flags |= SNOR_F_USE_FSR;
	if (info->flags & SPI_NOR_HAS_TB)
		nor->flags |= SNOR_F_HAS_SR_TB;
	if (info->flags & NO_CHIP_ERASE)
		nor->flags |= SNOR_F_NO_OP_CHIP_ERASE;
	if (info->flags & USE_CLSR)
		nor->flags |= SNOR_F_USE_CLSR;

	if (info->flags & SPI_NOR_NO_ERASE)
		mtd->flags |= MTD_NO_ERASE;

	mtd->dev.parent = dev;
	nor->page_size = params.page_size;
	mtd->writebufsize = nor->page_size;

	if (np) {
		/* If we were instantiated by DT, use it */
		if (of_property_read_bool(np, "m25p,fast-read"))
			params.hwcaps.mask |= SNOR_HWCAPS_READ_FAST;
		else
			params.hwcaps.mask &= ~SNOR_HWCAPS_READ_FAST;
	} else {
		/* If we weren't instantiated by DT, default to fast-read */
		params.hwcaps.mask |= SNOR_HWCAPS_READ_FAST;
	}

	if (of_property_read_bool(np, "broken-flash-reset"))
		nor->flags |= SNOR_F_BROKEN_RESET;

	/* Some devices cannot do fast-read, no matter what DT tells us */
	if (info->flags & SPI_NOR_NO_FR)
		params.hwcaps.mask &= ~SNOR_HWCAPS_READ_FAST;

	/*
	 * Configure the SPI memory:
	 * - select op codes for (Fast) Read, Page Program and Sector Erase.
	 * - set the number of dummy cycles (mode cycles + wait states).
	 * - set the SPI protocols for register and memory accesses.
	 * - set the Quad Enable bit if needed (required by SPI x-y-4 protos).
	 */
	ret = spi_nor_setup(nor, info, &params, hwcaps);
	if (ret)
		return ret;

	if (nor->addr_width) {
		/* already configured from SFDP */
	} else if (info->addr_width) {
		nor->addr_width = info->addr_width;
	} else if (mtd->size > 0x1000000) {
		/* enable 4-byte addressing if the device exceeds 16MiB */
		nor->addr_width = 4;
		if (JEDEC_MFR(info) == SNOR_MFR_SPANSION ||
		    info->flags & SPI_NOR_4B_OPCODES)
			spi_nor_set_4byte_opcodes(nor, info);
	} else {
		nor->addr_width = 3;
	}

	if (nor->addr_width > SPI_NOR_MAX_ADDR_WIDTH) {
		dev_err(dev, "address width is too large: %u\n",
			nor->addr_width);
		return -EINVAL;
	}

	if (info->flags & SPI_S3AN) {
		ret = s3an_nor_scan(info, nor);
		if (ret)
			return ret;
	}

	/* Send all the required SPI flash commands to initialize device */
	nor->info = info;
	ret = spi_nor_init(nor);
	if (ret)
		return ret;

	dev_info(dev, "%s (%lld Kbytes)\n", info->name,
			(long long)mtd->size >> 10);

	dev_dbg(dev,
		"mtd .name = %s, .size = 0x%llx (%lldMiB), "
		".erasesize = 0x%.8x (%uKiB) .numeraseregions = %d\n",
		mtd->name, (long long)mtd->size, (long long)(mtd->size >> 20),
		mtd->erasesize, mtd->erasesize / 1024, mtd->numeraseregions);

	if (mtd->numeraseregions)
		for (i = 0; i < mtd->numeraseregions; i++)
			dev_dbg(dev,
				"mtd.eraseregions[%d] = { .offset = 0x%llx, "
				".erasesize = 0x%.8x (%uKiB), "
				".numblocks = %d }\n",
				i, (long long)mtd->eraseregions[i].offset,
				mtd->eraseregions[i].erasesize,
				mtd->eraseregions[i].erasesize / 1024,
				mtd->eraseregions[i].numblocks);
	return 0;
}