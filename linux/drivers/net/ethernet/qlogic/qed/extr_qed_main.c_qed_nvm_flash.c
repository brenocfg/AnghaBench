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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct qed_dev {TYPE_1__* pdev; } ;
struct firmware {int size; int /*<<< orphan*/ * data; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (struct qed_dev*,char*,...) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct qed_dev*,int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ *,int) ; 
 int EINVAL ; 
 int FW_MSG_CODE_MASK ; 
#define  FW_MSG_CODE_NVM_OK 135 
#define  FW_MSG_CODE_NVM_PUT_FILE_FINISH_OK 134 
#define  FW_MSG_CODE_OK 133 
#define  FW_MSG_CODE_PHY_OK 132 
 int /*<<< orphan*/  NETIF_MSG_DRV ; 
#define  QED_NVM_FLASH_CMD_FILE_DATA 131 
#define  QED_NVM_FLASH_CMD_FILE_START 130 
#define  QED_NVM_FLASH_CMD_NVM_CFG_ID 129 
#define  QED_NVM_FLASH_CMD_NVM_CHANGE 128 
 scalar_t__ qed_mcp_nvm_resp (struct qed_dev*,int /*<<< orphan*/ *) ; 
 int qed_nvm_flash_cfg_write (struct qed_dev*,int /*<<< orphan*/  const**) ; 
 int qed_nvm_flash_image_access (struct qed_dev*,int /*<<< orphan*/  const**,int*) ; 
 int qed_nvm_flash_image_file_data (struct qed_dev*,int /*<<< orphan*/  const**,int*) ; 
 int qed_nvm_flash_image_file_start (struct qed_dev*,int /*<<< orphan*/  const**,int*) ; 
 int qed_nvm_flash_image_validate (struct qed_dev*,struct firmware const*,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qed_nvm_flash(struct qed_dev *cdev, const char *name)
{
	const struct firmware *image;
	const u8 *data, *data_end;
	u32 cmd_type;
	int rc;

	rc = request_firmware(&image, name, &cdev->pdev->dev);
	if (rc) {
		DP_ERR(cdev, "Failed to find '%s'\n", name);
		return rc;
	}

	DP_VERBOSE(cdev, NETIF_MSG_DRV,
		   "Flashing '%s' - firmware's data at %p, size is %08x\n",
		   name, image->data, (u32)image->size);
	data = image->data;
	data_end = data + image->size;

	rc = qed_nvm_flash_image_validate(cdev, image, &data);
	if (rc)
		goto exit;

	while (data < data_end) {
		bool check_resp = false;

		/* Parse the actual command */
		cmd_type = *((u32 *)data);
		switch (cmd_type) {
		case QED_NVM_FLASH_CMD_FILE_DATA:
			rc = qed_nvm_flash_image_file_data(cdev, &data,
							   &check_resp);
			break;
		case QED_NVM_FLASH_CMD_FILE_START:
			rc = qed_nvm_flash_image_file_start(cdev, &data,
							    &check_resp);
			break;
		case QED_NVM_FLASH_CMD_NVM_CHANGE:
			rc = qed_nvm_flash_image_access(cdev, &data,
							&check_resp);
			break;
		case QED_NVM_FLASH_CMD_NVM_CFG_ID:
			rc = qed_nvm_flash_cfg_write(cdev, &data);
			break;
		default:
			DP_ERR(cdev, "Unknown command %08x\n", cmd_type);
			rc = -EINVAL;
			goto exit;
		}

		if (rc) {
			DP_ERR(cdev, "Command %08x failed\n", cmd_type);
			goto exit;
		}

		/* Check response if needed */
		if (check_resp) {
			u32 mcp_response = 0;

			if (qed_mcp_nvm_resp(cdev, (u8 *)&mcp_response)) {
				DP_ERR(cdev, "Failed getting MCP response\n");
				rc = -EINVAL;
				goto exit;
			}

			switch (mcp_response & FW_MSG_CODE_MASK) {
			case FW_MSG_CODE_OK:
			case FW_MSG_CODE_NVM_OK:
			case FW_MSG_CODE_NVM_PUT_FILE_FINISH_OK:
			case FW_MSG_CODE_PHY_OK:
				break;
			default:
				DP_ERR(cdev, "MFW returns error: %08x\n",
				       mcp_response);
				rc = -EINVAL;
				goto exit;
			}
		}
	}

exit:
	release_firmware(image);

	return rc;
}