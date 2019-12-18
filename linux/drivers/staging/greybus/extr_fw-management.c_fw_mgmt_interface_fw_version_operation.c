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
struct gb_fw_mgmt_interface_fw_version_response {int /*<<< orphan*/  firmware_tag; int /*<<< orphan*/  minor; int /*<<< orphan*/  major; } ;
struct gb_connection {int dummy; } ;
struct fw_mgmt_ioc_get_intf_version {char* firmware_tag; void* minor; void* major; } ;
struct fw_mgmt {int /*<<< orphan*/  parent; struct gb_connection* connection; } ;
typedef  int /*<<< orphan*/  response ;

/* Variables and functions */
 int GB_FIRMWARE_TAG_MAX_SIZE ; 
 int /*<<< orphan*/  GB_FW_MGMT_TYPE_INTERFACE_FW_VERSION ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int gb_operation_sync (struct gb_connection*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct gb_fw_mgmt_interface_fw_version_response*,int) ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int fw_mgmt_interface_fw_version_operation(struct fw_mgmt *fw_mgmt,
		struct fw_mgmt_ioc_get_intf_version *fw_info)
{
	struct gb_connection *connection = fw_mgmt->connection;
	struct gb_fw_mgmt_interface_fw_version_response response;
	int ret;

	ret = gb_operation_sync(connection,
				GB_FW_MGMT_TYPE_INTERFACE_FW_VERSION, NULL, 0,
				&response, sizeof(response));
	if (ret) {
		dev_err(fw_mgmt->parent,
			"failed to get interface firmware version (%d)\n", ret);
		return ret;
	}

	fw_info->major = le16_to_cpu(response.major);
	fw_info->minor = le16_to_cpu(response.minor);

	strncpy(fw_info->firmware_tag, response.firmware_tag,
		GB_FIRMWARE_TAG_MAX_SIZE);

	/*
	 * The firmware-tag should be NULL terminated, otherwise throw error but
	 * don't fail.
	 */
	if (fw_info->firmware_tag[GB_FIRMWARE_TAG_MAX_SIZE - 1] != '\0') {
		dev_err(fw_mgmt->parent,
			"fw-version: firmware-tag is not NULL terminated\n");
		fw_info->firmware_tag[GB_FIRMWARE_TAG_MAX_SIZE - 1] = '\0';
	}

	return 0;
}