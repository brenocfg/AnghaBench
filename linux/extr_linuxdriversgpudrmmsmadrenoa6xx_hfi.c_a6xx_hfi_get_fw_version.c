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
typedef  int /*<<< orphan*/  u32 ;
struct a6xx_hfi_msg_fw_version {int supported_version; int /*<<< orphan*/  member_0; } ;
struct a6xx_gmu {int dummy; } ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  HFI_H2F_MSG_FW_VERSION ; 
 int a6xx_hfi_send_msg (struct a6xx_gmu*,int /*<<< orphan*/ ,struct a6xx_hfi_msg_fw_version*,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int a6xx_hfi_get_fw_version(struct a6xx_gmu *gmu, u32 *version)
{
	struct a6xx_hfi_msg_fw_version msg = { 0 };

	/* Currently supporting version 1.1 */
	msg.supported_version = (1 << 28) | (1 << 16);

	return a6xx_hfi_send_msg(gmu, HFI_H2F_MSG_FW_VERSION, &msg, sizeof(msg),
		version, sizeof(*version));
}