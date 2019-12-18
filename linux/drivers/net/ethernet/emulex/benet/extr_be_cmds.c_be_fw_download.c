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
struct image_hdr {int /*<<< orphan*/  imageid; } ;
struct flash_file_hdr_g3 {int /*<<< orphan*/  num_imgs; } ;
struct firmware {scalar_t__ data; } ;
struct device {int dummy; } ;
struct be_dma_mem {int size; int /*<<< orphan*/  dma; int /*<<< orphan*/  va; } ;
struct be_cmd_write_flashrom {int dummy; } ;
struct be_adapter {TYPE_1__* pdev; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BE2_chip (struct be_adapter*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  be_check_ufi_compatibility (struct be_adapter*,struct flash_file_hdr_g3*) ; 
 int be_flash_BEx (struct be_adapter*,struct firmware const*,struct be_dma_mem*,int) ; 
 int be_flash_skyhawk (struct be_adapter*,struct firmware const*,struct be_dma_mem*,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  dma_alloc_coherent (struct device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ skyhawk_chip (struct be_adapter*) ; 

int be_fw_download(struct be_adapter *adapter, const struct firmware *fw)
{
	struct device *dev = &adapter->pdev->dev;
	struct flash_file_hdr_g3 *fhdr3;
	struct image_hdr *img_hdr_ptr;
	int status = 0, i, num_imgs;
	struct be_dma_mem flash_cmd;

	fhdr3 = (struct flash_file_hdr_g3 *)fw->data;
	if (!be_check_ufi_compatibility(adapter, fhdr3)) {
		dev_err(dev, "Flash image is not compatible with adapter\n");
		return -EINVAL;
	}

	flash_cmd.size = sizeof(struct be_cmd_write_flashrom);
	flash_cmd.va = dma_alloc_coherent(dev, flash_cmd.size, &flash_cmd.dma,
					  GFP_KERNEL);
	if (!flash_cmd.va)
		return -ENOMEM;

	num_imgs = le32_to_cpu(fhdr3->num_imgs);
	for (i = 0; i < num_imgs; i++) {
		img_hdr_ptr = (struct image_hdr *)(fw->data +
				(sizeof(struct flash_file_hdr_g3) +
				 i * sizeof(struct image_hdr)));
		if (!BE2_chip(adapter) &&
		    le32_to_cpu(img_hdr_ptr->imageid) != 1)
			continue;

		if (skyhawk_chip(adapter))
			status = be_flash_skyhawk(adapter, fw, &flash_cmd,
						  num_imgs);
		else
			status = be_flash_BEx(adapter, fw, &flash_cmd,
					      num_imgs);
	}

	dma_free_coherent(dev, flash_cmd.size, flash_cmd.va, flash_cmd.dma);
	if (!status)
		dev_info(dev, "Firmware flashed successfully\n");

	return status;
}