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
typedef  int u32 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct firmware {int size; scalar_t__ data; } ;

/* Variables and functions */
 struct firmware const* bfi_fw ; 
 int /*<<< orphan*/  dev_alert (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  le32_to_cpus (int*) ; 
 scalar_t__ request_firmware (struct firmware const**,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32 *
cna_read_firmware(struct pci_dev *pdev, u32 **bfi_image,
			u32 *bfi_image_size, char *fw_name)
{
	const struct firmware *fw;
	u32 n;

	if (request_firmware(&fw, fw_name, &pdev->dev)) {
		dev_alert(&pdev->dev, "can't load firmware %s\n", fw_name);
		goto error;
	}

	*bfi_image = (u32 *)fw->data;
	*bfi_image_size = fw->size/sizeof(u32);
	bfi_fw = fw;

	/* Convert loaded firmware to host order as it is stored in file
	 * as sequence of LE32 integers.
	 */
	for (n = 0; n < *bfi_image_size; n++)
		le32_to_cpus(*bfi_image + n);

	return *bfi_image;
error:
	return NULL;
}