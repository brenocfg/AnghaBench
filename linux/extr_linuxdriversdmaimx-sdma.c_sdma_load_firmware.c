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
struct sdma_script_start_addrs {int /*<<< orphan*/  ram_code_start_addr; } ;
struct sdma_firmware_header {scalar_t__ magic; int ram_code_start; int ram_code_size; int version_major; int script_addrs_start; int /*<<< orphan*/  version_minor; } ;
struct sdma_engine {int /*<<< orphan*/  dev; int /*<<< orphan*/  clk_ahb; int /*<<< orphan*/  clk_ipg; int /*<<< orphan*/  script_number; } ;
struct firmware {int size; scalar_t__ data; } ;

/* Variables and functions */
 scalar_t__ SDMA_FIRMWARE_MAGIC ; 
 int /*<<< orphan*/  SDMA_SCRIPT_ADDRS_ARRAY_SIZE_V1 ; 
 int /*<<< orphan*/  SDMA_SCRIPT_ADDRS_ARRAY_SIZE_V2 ; 
 int /*<<< orphan*/  SDMA_SCRIPT_ADDRS_ARRAY_SIZE_V3 ; 
 int /*<<< orphan*/  SDMA_SCRIPT_ADDRS_ARRAY_SIZE_V4 ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int /*<<< orphan*/  sdma_add_scripts (struct sdma_engine*,struct sdma_script_start_addrs const*) ; 
 int /*<<< orphan*/  sdma_load_script (struct sdma_engine*,unsigned short*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sdma_load_firmware(const struct firmware *fw, void *context)
{
	struct sdma_engine *sdma = context;
	const struct sdma_firmware_header *header;
	const struct sdma_script_start_addrs *addr;
	unsigned short *ram_code;

	if (!fw) {
		dev_info(sdma->dev, "external firmware not found, using ROM firmware\n");
		/* In this case we just use the ROM firmware. */
		return;
	}

	if (fw->size < sizeof(*header))
		goto err_firmware;

	header = (struct sdma_firmware_header *)fw->data;

	if (header->magic != SDMA_FIRMWARE_MAGIC)
		goto err_firmware;
	if (header->ram_code_start + header->ram_code_size > fw->size)
		goto err_firmware;
	switch (header->version_major) {
	case 1:
		sdma->script_number = SDMA_SCRIPT_ADDRS_ARRAY_SIZE_V1;
		break;
	case 2:
		sdma->script_number = SDMA_SCRIPT_ADDRS_ARRAY_SIZE_V2;
		break;
	case 3:
		sdma->script_number = SDMA_SCRIPT_ADDRS_ARRAY_SIZE_V3;
		break;
	case 4:
		sdma->script_number = SDMA_SCRIPT_ADDRS_ARRAY_SIZE_V4;
		break;
	default:
		dev_err(sdma->dev, "unknown firmware version\n");
		goto err_firmware;
	}

	addr = (void *)header + header->script_addrs_start;
	ram_code = (void *)header + header->ram_code_start;

	clk_enable(sdma->clk_ipg);
	clk_enable(sdma->clk_ahb);
	/* download the RAM image for SDMA */
	sdma_load_script(sdma, ram_code,
			header->ram_code_size,
			addr->ram_code_start_addr);
	clk_disable(sdma->clk_ipg);
	clk_disable(sdma->clk_ahb);

	sdma_add_scripts(sdma, addr);

	dev_info(sdma->dev, "loaded firmware %d.%d\n",
			header->version_major,
			header->version_minor);

err_firmware:
	release_firmware(fw);
}