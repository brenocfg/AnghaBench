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
#define  BNX_DIR_TYPE_APE_FW 136 
#define  BNX_DIR_TYPE_APE_PATCH 135 
#define  BNX_DIR_TYPE_BONO_FW 134 
#define  BNX_DIR_TYPE_BONO_PATCH 133 
#define  BNX_DIR_TYPE_BOOTCODE 132 
#define  BNX_DIR_TYPE_BOOTCODE_2 131 
#define  BNX_DIR_TYPE_CHIMP_PATCH 130 
#define  BNX_DIR_TYPE_KONG_FW 129 
#define  BNX_DIR_TYPE_KONG_PATCH 128 

__attribute__((used)) static bool bnxt_dir_type_is_ape_bin_format(u16 dir_type)
{
	switch (dir_type) {
	case BNX_DIR_TYPE_CHIMP_PATCH:
	case BNX_DIR_TYPE_BOOTCODE:
	case BNX_DIR_TYPE_BOOTCODE_2:
	case BNX_DIR_TYPE_APE_FW:
	case BNX_DIR_TYPE_APE_PATCH:
	case BNX_DIR_TYPE_KONG_FW:
	case BNX_DIR_TYPE_KONG_PATCH:
	case BNX_DIR_TYPE_BONO_FW:
	case BNX_DIR_TYPE_BONO_PATCH:
		return true;
	}

	return false;
}