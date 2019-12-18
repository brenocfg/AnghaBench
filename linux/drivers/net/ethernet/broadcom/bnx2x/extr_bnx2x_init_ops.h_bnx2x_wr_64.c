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
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_WR_DMAE_LEN (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void bnx2x_wr_64(struct bnx2x *bp, u32 reg, u32 val_lo,
			u32 val_hi)
{
	u32 wb_write[2];

	wb_write[0] = val_lo;
	wb_write[1] = val_hi;
	REG_WR_DMAE_LEN(bp, reg, wb_write, 2);
}