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
typedef  int u32 ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*,int) ; 
#define  FW_MSG_CODE_DRV_LOAD_COMMON 131 
#define  FW_MSG_CODE_DRV_LOAD_COMMON_CHIP 130 
#define  FW_MSG_CODE_DRV_LOAD_FUNCTION 129 
#define  FW_MSG_CODE_DRV_LOAD_PORT 128 
 int /*<<< orphan*/  bnx2x_init_internal_common (struct bnx2x*) ; 

__attribute__((used)) static void bnx2x_init_internal(struct bnx2x *bp, u32 load_code)
{
	switch (load_code) {
	case FW_MSG_CODE_DRV_LOAD_COMMON:
	case FW_MSG_CODE_DRV_LOAD_COMMON_CHIP:
		bnx2x_init_internal_common(bp);
		/* no break */

	case FW_MSG_CODE_DRV_LOAD_PORT:
		/* nothing to do */
		/* no break */

	case FW_MSG_CODE_DRV_LOAD_FUNCTION:
		/* internal memory per function is
		   initialized inside bnx2x_pf_init */
		break;

	default:
		BNX2X_ERR("Unknown load_code (0x%x) from MCP\n", load_code);
		break;
	}
}