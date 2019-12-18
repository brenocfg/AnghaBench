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
struct firmware {int /*<<< orphan*/  size; } ;
struct TYPE_4__ {int /*<<< orphan*/  vaddr; int /*<<< orphan*/  paddr; int /*<<< orphan*/  size; struct firmware* firmware; } ;
struct falcon {TYPE_2__ firmware; TYPE_1__* ops; int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* free ) (struct falcon*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* alloc ) (struct falcon*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  falcon_copy_firmware_image (struct falcon*,struct firmware const*) ; 
 int falcon_parse_firmware_image (struct falcon*) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int /*<<< orphan*/  stub1 (struct falcon*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (struct falcon*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int falcon_load_firmware(struct falcon *falcon)
{
	const struct firmware *firmware = falcon->firmware.firmware;
	int err;

	falcon->firmware.size = firmware->size;

	/* allocate iova space for the firmware */
	falcon->firmware.vaddr = falcon->ops->alloc(falcon, firmware->size,
						    &falcon->firmware.paddr);
	if (IS_ERR(falcon->firmware.vaddr)) {
		dev_err(falcon->dev, "DMA memory mapping failed\n");
		return PTR_ERR(falcon->firmware.vaddr);
	}

	/* copy firmware image into local area. this also ensures endianness */
	falcon_copy_firmware_image(falcon, firmware);

	/* parse the image data */
	err = falcon_parse_firmware_image(falcon);
	if (err < 0) {
		dev_err(falcon->dev, "failed to parse firmware image\n");
		goto err_setup_firmware_image;
	}

	release_firmware(firmware);
	falcon->firmware.firmware = NULL;

	return 0;

err_setup_firmware_image:
	falcon->ops->free(falcon, falcon->firmware.size,
			  falcon->firmware.paddr, falcon->firmware.vaddr);

	return err;
}