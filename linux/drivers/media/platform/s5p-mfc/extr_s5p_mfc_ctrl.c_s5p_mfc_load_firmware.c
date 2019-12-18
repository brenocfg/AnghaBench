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
struct TYPE_6__ {scalar_t__ size; int /*<<< orphan*/  virt; } ;
struct s5p_mfc_dev {int fw_get_done; int fw_ver; TYPE_3__ fw_buf; TYPE_2__* plat_dev; TYPE_1__* variant; } ;
struct firmware {scalar_t__ size; int /*<<< orphan*/  data; } ;
typedef  enum s5p_mfc_fw_ver { ____Placeholder_s5p_mfc_fw_ver } s5p_mfc_fw_ver ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/ * fw_name; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int MFC_FW_MAX_VERSIONS ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mfc_debug_enter () ; 
 int /*<<< orphan*/  mfc_debug_leave () ; 
 int /*<<< orphan*/  mfc_err (char*) ; 
 int /*<<< orphan*/  release_firmware (struct firmware*) ; 
 int request_firmware (struct firmware const**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wmb () ; 

int s5p_mfc_load_firmware(struct s5p_mfc_dev *dev)
{
	struct firmware *fw_blob;
	int i, err = -EINVAL;

	/* Firmware has to be present as a separate file or compiled
	 * into kernel. */
	mfc_debug_enter();

	if (dev->fw_get_done)
		return 0;

	for (i = MFC_FW_MAX_VERSIONS - 1; i >= 0; i--) {
		if (!dev->variant->fw_name[i])
			continue;
		err = request_firmware((const struct firmware **)&fw_blob,
				dev->variant->fw_name[i], &dev->plat_dev->dev);
		if (!err) {
			dev->fw_ver = (enum s5p_mfc_fw_ver) i;
			break;
		}
	}

	if (err != 0) {
		mfc_err("Firmware is not present in the /lib/firmware directory nor compiled in kernel\n");
		return -EINVAL;
	}
	if (fw_blob->size > dev->fw_buf.size) {
		mfc_err("MFC firmware is too big to be loaded\n");
		release_firmware(fw_blob);
		return -ENOMEM;
	}
	memcpy(dev->fw_buf.virt, fw_blob->data, fw_blob->size);
	wmb();
	dev->fw_get_done = true;
	release_firmware(fw_blob);
	mfc_debug_leave();
	return 0;
}