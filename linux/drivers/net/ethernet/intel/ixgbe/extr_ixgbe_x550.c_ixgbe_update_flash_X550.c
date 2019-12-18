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
struct TYPE_2__ {int /*<<< orphan*/  checksum; int /*<<< orphan*/  buf_lenl; scalar_t__ buf_lenh; int /*<<< orphan*/  cmd; } ;
union ixgbe_hic_hdr2 {TYPE_1__ req; } ;
struct ixgbe_hw {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int /*<<< orphan*/  FW_DEFAULT_CHECKSUM ; 
 int /*<<< orphan*/  FW_SHADOW_RAM_DUMP_CMD ; 
 int /*<<< orphan*/  FW_SHADOW_RAM_DUMP_LEN ; 
 int /*<<< orphan*/  IXGBE_HI_COMMAND_TIMEOUT ; 
 int /*<<< orphan*/  ixgbe_host_interface_command (struct ixgbe_hw*,union ixgbe_hic_hdr2*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static s32 ixgbe_update_flash_X550(struct ixgbe_hw *hw)
{
	s32 status = 0;
	union ixgbe_hic_hdr2 buffer;

	buffer.req.cmd = FW_SHADOW_RAM_DUMP_CMD;
	buffer.req.buf_lenh = 0;
	buffer.req.buf_lenl = FW_SHADOW_RAM_DUMP_LEN;
	buffer.req.checksum = FW_DEFAULT_CHECKSUM;

	status = ixgbe_host_interface_command(hw, &buffer, sizeof(buffer),
					      IXGBE_HI_COMMAND_TIMEOUT, false);
	return status;
}