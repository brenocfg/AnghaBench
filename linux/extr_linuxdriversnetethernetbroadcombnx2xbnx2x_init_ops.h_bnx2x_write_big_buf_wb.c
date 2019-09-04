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
struct bnx2x {scalar_t__ dmae_ready; } ;

/* Variables and functions */
 scalar_t__ CHIP_IS_E1 (struct bnx2x*) ; 
 int /*<<< orphan*/  GUNZIP_BUF (struct bnx2x*) ; 
 int /*<<< orphan*/  GUNZIP_PHYS (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_init_ind_wr (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_init_str_wr (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_write_dmae_phys_len (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnx2x_write_big_buf_wb(struct bnx2x *bp, u32 addr, u32 len)
{
	if (bp->dmae_ready)
		bnx2x_write_dmae_phys_len(bp, GUNZIP_PHYS(bp), addr, len);

	/* in E1 chips BIOS initiated ZLR may interrupt widebus writes */
	else if (CHIP_IS_E1(bp))
		bnx2x_init_ind_wr(bp, addr, GUNZIP_BUF(bp), len);

	/* in later chips PXP root complex handles BIOS ZLR w/o interrupting */
	else
		bnx2x_init_str_wr(bp, addr, GUNZIP_BUF(bp), len);
}