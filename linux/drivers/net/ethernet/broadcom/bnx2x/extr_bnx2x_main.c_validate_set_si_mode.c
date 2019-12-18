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
typedef  size_t u8 ;
typedef  int u32 ;
struct bnx2x {void** mf_config; int /*<<< orphan*/  mf_mode; } ;
struct TYPE_2__ {int /*<<< orphan*/  config; int /*<<< orphan*/  mac_upper; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_DEV_INFO (char*) ; 
 size_t BP_ABS_FUNC (struct bnx2x*) ; 
 size_t BP_VN (struct bnx2x*) ; 
 void* MF_CFG_RD (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MULTI_FUNCTION_SI ; 
 TYPE_1__* func_mf_config ; 

__attribute__((used)) static void validate_set_si_mode(struct bnx2x *bp)
{
	u8 func = BP_ABS_FUNC(bp);
	u32 val;

	val = MF_CFG_RD(bp, func_mf_config[func].mac_upper);

	/* check for legal mac (upper bytes) */
	if (val != 0xffff) {
		bp->mf_mode = MULTI_FUNCTION_SI;
		bp->mf_config[BP_VN(bp)] =
			MF_CFG_RD(bp, func_mf_config[func].config);
	} else
		BNX2X_DEV_INFO("illegal MAC address for SI\n");
}