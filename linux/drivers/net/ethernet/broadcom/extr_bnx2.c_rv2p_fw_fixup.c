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

/* Variables and functions */
 int /*<<< orphan*/  RV2P_BD_PAGE_SIZE ; 
 int /*<<< orphan*/  RV2P_BD_PAGE_SIZE_MSK ; 
#define  RV2P_P1_FIXUP_PAGE_SIZE_IDX 128 

__attribute__((used)) static u32
rv2p_fw_fixup(u32 rv2p_proc, int idx, u32 loc, u32 rv2p_code)
{
	switch (idx) {
	case RV2P_P1_FIXUP_PAGE_SIZE_IDX:
		rv2p_code &= ~RV2P_BD_PAGE_SIZE_MSK;
		rv2p_code |= RV2P_BD_PAGE_SIZE;
		break;
	}
	return rv2p_code;
}