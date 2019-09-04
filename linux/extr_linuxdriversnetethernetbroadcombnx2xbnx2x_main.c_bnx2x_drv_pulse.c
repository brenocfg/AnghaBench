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
struct bnx2x {int /*<<< orphan*/  fw_drv_pulse_wr_seq; } ;
struct TYPE_2__ {int /*<<< orphan*/  drv_pulse_mb; } ;

/* Variables and functions */
 size_t BP_FW_MB_IDX (struct bnx2x*) ; 
 int /*<<< orphan*/  SHMEM_WR (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* func_mb ; 

void bnx2x_drv_pulse(struct bnx2x *bp)
{
	SHMEM_WR(bp, func_mb[BP_FW_MB_IDX(bp)].drv_pulse_mb,
		 bp->fw_drv_pulse_wr_seq);
}