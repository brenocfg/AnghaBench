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
typedef  int u16 ;

/* Variables and functions */
#define  BNX_DIR_TYPE_AVS 136 
#define  BNX_DIR_TYPE_CCM 135 
#define  BNX_DIR_TYPE_EXP_ROM_MBA 134 
#define  BNX_DIR_TYPE_EXT_PHY 133 
#define  BNX_DIR_TYPE_ISCSI_BOOT 132 
#define  BNX_DIR_TYPE_ISCSI_BOOT_IPV4N6 131 
#define  BNX_DIR_TYPE_ISCSI_BOOT_IPV6 130 
#define  BNX_DIR_TYPE_PCIE 129 
#define  BNX_DIR_TYPE_TSCF_UCODE 128 

__attribute__((used)) static bool bnxt_dir_type_is_other_exec_format(u16 dir_type)
{
	switch (dir_type) {
	case BNX_DIR_TYPE_AVS:
	case BNX_DIR_TYPE_EXP_ROM_MBA:
	case BNX_DIR_TYPE_PCIE:
	case BNX_DIR_TYPE_TSCF_UCODE:
	case BNX_DIR_TYPE_EXT_PHY:
	case BNX_DIR_TYPE_CCM:
	case BNX_DIR_TYPE_ISCSI_BOOT:
	case BNX_DIR_TYPE_ISCSI_BOOT_IPV6:
	case BNX_DIR_TYPE_ISCSI_BOOT_IPV4N6:
		return true;
	}

	return false;
}