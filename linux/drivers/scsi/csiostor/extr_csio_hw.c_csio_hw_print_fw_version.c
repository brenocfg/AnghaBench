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
struct csio_hw {int /*<<< orphan*/  fwrev; } ;

/* Variables and functions */
 int /*<<< orphan*/  FW_HDR_FW_VER_BUILD_G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FW_HDR_FW_VER_MAJOR_G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FW_HDR_FW_VER_MICRO_G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FW_HDR_FW_VER_MINOR_G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csio_info (struct csio_hw*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
csio_hw_print_fw_version(struct csio_hw *hw, char *str)
{
	csio_info(hw, "%s: %u.%u.%u.%u\n", str,
		    FW_HDR_FW_VER_MAJOR_G(hw->fwrev),
		    FW_HDR_FW_VER_MINOR_G(hw->fwrev),
		    FW_HDR_FW_VER_MICRO_G(hw->fwrev),
		    FW_HDR_FW_VER_BUILD_G(hw->fwrev));
}