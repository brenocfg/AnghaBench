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
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  int uint16_t ;
struct softing {TYPE_3__* pdev; int /*<<< orphan*/ * dpram; TYPE_2__* pdat; } ;
struct firmware {size_t size; scalar_t__* data; } ;
typedef  int int8_t ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {size_t offs; scalar_t__ addr; } ;
struct TYPE_5__ {TYPE_1__ app; } ;

/* Variables and functions */
 int DPRAM_COMMAND ; 
 int DPRAM_RECEIPT ; 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  dev_alert (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,char const*,unsigned long) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,char const*) ; 
 int fw_parse (scalar_t__ const**,int*,scalar_t__*,int*,scalar_t__ const**) ; 
 unsigned int ioread16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite16 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite32 (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite8 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy_toio (int /*<<< orphan*/ *,scalar_t__ const*,int) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,char const*,int /*<<< orphan*/ *) ; 
 int softing_bootloader_command (struct softing*,int,char*) ; 
 scalar_t__ strncmp (char*,scalar_t__ const*,int) ; 

int softing_load_app_fw(const char *file, struct softing *card)
{
	const struct firmware *fw;
	const uint8_t *mem, *end, *dat;
	int ret, j;
	uint16_t type, len;
	uint32_t addr, start_addr = 0;
	unsigned int sum, rx_sum;
	int8_t type_end = 0, type_entrypoint = 0;

	ret = request_firmware(&fw, file, &card->pdev->dev);
	if (ret) {
		dev_alert(&card->pdev->dev, "request_firmware(%s) got %i\n",
			file, ret);
		return ret;
	}
	dev_dbg(&card->pdev->dev, "firmware(%s) got %lu bytes\n",
		file, (unsigned long)fw->size);
	/* parse the firmware */
	mem = fw->data;
	end = &mem[fw->size];
	/* look for header record */
	ret = fw_parse(&mem, &type, &addr, &len, &dat);
	if (ret)
		goto failed;
	ret = -EINVAL;
	if (type != 0xffff) {
		dev_alert(&card->pdev->dev, "firmware starts with type 0x%x\n",
			type);
		goto failed;
	}
	if (strncmp("Structured Binary Format, Softing GmbH", dat, len)) {
		dev_alert(&card->pdev->dev, "firmware string '%.*s' fault\n",
				len, dat);
		goto failed;
	}
	/* ok, we had a header */
	while (mem < end) {
		ret = fw_parse(&mem, &type, &addr, &len, &dat);
		if (ret)
			goto failed;

		if (type == 3) {
			/* start address */
			start_addr = addr;
			type_entrypoint = 1;
			continue;
		} else if (type == 1) {
			/* eof */
			type_end = 1;
			break;
		} else if (type != 0) {
			dev_alert(&card->pdev->dev,
					"unknown record type 0x%04x\n", type);
			ret = -EINVAL;
			goto failed;
		}

		/* regualar data */
		for (sum = 0, j = 0; j < len; ++j)
			sum += dat[j];
		/* work in 16bit (target) */
		sum &= 0xffff;

		memcpy_toio(&card->dpram[card->pdat->app.offs], dat, len);
		iowrite32(card->pdat->app.offs + card->pdat->app.addr,
				&card->dpram[DPRAM_COMMAND + 2]);
		iowrite32(addr, &card->dpram[DPRAM_COMMAND + 6]);
		iowrite16(len, &card->dpram[DPRAM_COMMAND + 10]);
		iowrite8(1, &card->dpram[DPRAM_COMMAND + 12]);
		ret = softing_bootloader_command(card, 1, "loading app.");
		if (ret < 0)
			goto failed;
		/* verify checksum */
		rx_sum = ioread16(&card->dpram[DPRAM_RECEIPT + 2]);
		if (rx_sum != sum) {
			dev_alert(&card->pdev->dev, "SRAM seems to be damaged"
				", wanted 0x%04x, got 0x%04x\n", sum, rx_sum);
			ret = -EIO;
			goto failed;
		}
	}
	if (!type_end || !type_entrypoint)
		goto failed;
	/* start application in card */
	iowrite32(start_addr, &card->dpram[DPRAM_COMMAND + 2]);
	iowrite8(1, &card->dpram[DPRAM_COMMAND + 6]);
	ret = softing_bootloader_command(card, 3, "start app.");
	if (ret < 0)
		goto failed;
	ret = 0;
failed:
	release_firmware(fw);
	if (ret < 0)
		dev_info(&card->pdev->dev, "firmware %s failed\n", file);
	return ret;
}