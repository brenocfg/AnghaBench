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
struct spi_device {int /*<<< orphan*/  dev; } ;
struct flash_info {int flags; int /*<<< orphan*/  pageoffset; int /*<<< orphan*/  pagesize; int /*<<< orphan*/  nr_pages; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ IS_ERR (struct flash_info*) ; 
 int PTR_ERR (struct flash_info*) ; 
 int SUP_POW2PS ; 
 int add_dataflash (struct spi_device*,char*,int,int,int) ; 
 int add_dataflash_otp (struct spi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char) ; 
 int dataflash_status (struct spi_device*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int) ; 
 struct flash_info* jedec_probe (struct spi_device*) ; 

__attribute__((used)) static int dataflash_probe(struct spi_device *spi)
{
	int status;
	struct flash_info	*info;

	/*
	 * Try to detect dataflash by JEDEC ID.
	 * If it succeeds we know we have either a C or D part.
	 * D will support power of 2 pagesize option.
	 * Both support the security register, though with different
	 * write procedures.
	 */
	info = jedec_probe(spi);
	if (IS_ERR(info))
		return PTR_ERR(info);
	if (info != NULL)
		return add_dataflash_otp(spi, info->name, info->nr_pages,
				info->pagesize, info->pageoffset,
				(info->flags & SUP_POW2PS) ? 'd' : 'c');

	/*
	 * Older chips support only legacy commands, identifing
	 * capacity using bits in the status byte.
	 */
	status = dataflash_status(spi);
	if (status <= 0 || status == 0xff) {
		dev_dbg(&spi->dev, "status error %d\n", status);
		if (status == 0 || status == 0xff)
			status = -ENODEV;
		return status;
	}

	/* if there's a device there, assume it's dataflash.
	 * board setup should have set spi->max_speed_max to
	 * match f(car) for continuous reads, mode 0 or 3.
	 */
	switch (status & 0x3c) {
	case 0x0c:	/* 0 0 1 1 x x */
		status = add_dataflash(spi, "AT45DB011B", 512, 264, 9);
		break;
	case 0x14:	/* 0 1 0 1 x x */
		status = add_dataflash(spi, "AT45DB021B", 1024, 264, 9);
		break;
	case 0x1c:	/* 0 1 1 1 x x */
		status = add_dataflash(spi, "AT45DB041x", 2048, 264, 9);
		break;
	case 0x24:	/* 1 0 0 1 x x */
		status = add_dataflash(spi, "AT45DB081B", 4096, 264, 9);
		break;
	case 0x2c:	/* 1 0 1 1 x x */
		status = add_dataflash(spi, "AT45DB161x", 4096, 528, 10);
		break;
	case 0x34:	/* 1 1 0 1 x x */
		status = add_dataflash(spi, "AT45DB321x", 8192, 528, 10);
		break;
	case 0x38:	/* 1 1 1 x x x */
	case 0x3c:
		status = add_dataflash(spi, "AT45DB642x", 8192, 1056, 11);
		break;
	/* obsolete AT45DB1282 not (yet?) supported */
	default:
		dev_info(&spi->dev, "unsupported device (%x)\n",
				status & 0x3c);
		status = -ENODEV;
	}

	if (status < 0)
		dev_dbg(&spi->dev, "add_dataflash --> %d\n", status);

	return status;
}