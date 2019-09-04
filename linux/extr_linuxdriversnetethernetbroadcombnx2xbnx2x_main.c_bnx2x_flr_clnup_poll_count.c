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
 scalar_t__ CHIP_REV_IS_EMUL (struct bnx2x*) ; 
 scalar_t__ CHIP_REV_IS_FPGA (struct bnx2x*) ; 
 int FLR_POLL_CNT ; 

u32 bnx2x_flr_clnup_poll_count(struct bnx2x *bp)
{
	/* adjust polling timeout */
	if (CHIP_REV_IS_EMUL(bp))
		return FLR_POLL_CNT * 2000;

	if (CHIP_REV_IS_FPGA(bp))
		return FLR_POLL_CNT * 120;

	return FLR_POLL_CNT;
}