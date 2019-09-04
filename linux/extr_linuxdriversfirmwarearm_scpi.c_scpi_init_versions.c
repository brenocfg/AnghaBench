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
struct scpi_drvinfo {void* firmware_version; void* protocol_version; } ;
struct scp_capabilities {int /*<<< orphan*/  platform_version; int /*<<< orphan*/  protocol_version; } ;
typedef  int /*<<< orphan*/  caps ;
struct TYPE_2__ {scalar_t__ is_legacy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SCPI_CAPABILITIES ; 
 int EOPNOTSUPP ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 TYPE_1__* scpi_info ; 
 int scpi_send_message (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct scp_capabilities*,int) ; 

__attribute__((used)) static int scpi_init_versions(struct scpi_drvinfo *info)
{
	int ret;
	struct scp_capabilities caps;

	ret = scpi_send_message(CMD_SCPI_CAPABILITIES, NULL, 0,
				&caps, sizeof(caps));
	if (!ret) {
		info->protocol_version = le32_to_cpu(caps.protocol_version);
		info->firmware_version = le32_to_cpu(caps.platform_version);
	}
	/* Ignore error if not implemented */
	if (scpi_info->is_legacy && ret == -EOPNOTSUPP)
		return 0;

	return ret;
}