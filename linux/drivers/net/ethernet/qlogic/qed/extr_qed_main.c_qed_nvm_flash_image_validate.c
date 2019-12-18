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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct qed_dev {int dummy; } ;
struct firmware {int size; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (struct qed_dev*,char*,scalar_t__,...) ; 
 int EINVAL ; 
 scalar_t__ QED_NVM_FLASH_CMD_NVM_MAX ; 
 scalar_t__ QED_NVM_SIGNATURE ; 

__attribute__((used)) static int qed_nvm_flash_image_validate(struct qed_dev *cdev,
					const struct firmware *image,
					const u8 **data)
{
	u32 signature, len;

	/* Check minimum size */
	if (image->size < 12) {
		DP_ERR(cdev, "Image is too short [%08x]\n", (u32)image->size);
		return -EINVAL;
	}

	/* Check signature */
	signature = *((u32 *)(*data));
	if (signature != QED_NVM_SIGNATURE) {
		DP_ERR(cdev, "Wrong signature '%08x'\n", signature);
		return -EINVAL;
	}

	*data += 4;
	/* Validate internal size equals the image-size */
	len = *((u32 *)(*data));
	if (len != image->size) {
		DP_ERR(cdev, "Size mismatch: internal = %08x image = %08x\n",
		       len, (u32)image->size);
		return -EINVAL;
	}

	*data += 4;
	/* Make sure driver familiar with all commands necessary for this */
	if (*((u16 *)(*data)) >= QED_NVM_FLASH_CMD_NVM_MAX) {
		DP_ERR(cdev, "File contains unsupported commands [Need %04x]\n",
		       *((u16 *)(*data)));
		return -EINVAL;
	}

	*data += 4;

	return 0;
}