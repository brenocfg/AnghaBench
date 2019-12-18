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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 scalar_t__ BAR_CSTRORM_INTMEM ; 
 scalar_t__ BAR_TSTRORM_INTMEM ; 
 scalar_t__ BAR_USTRORM_INTMEM ; 
 scalar_t__ BAR_XSTRORM_INTMEM ; 
 scalar_t__ CSTORM_FUNC_EN_OFFSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WR8 (struct bnx2x*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ TSTORM_FUNC_EN_OFFSET (int /*<<< orphan*/ ) ; 
 scalar_t__ USTORM_FUNC_EN_OFFSET (int /*<<< orphan*/ ) ; 
 scalar_t__ XSTORM_FUNC_EN_OFFSET (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void storm_memset_func_en(struct bnx2x *bp, u16 abs_fid,
				 u8 enable)
{
	REG_WR8(bp, BAR_XSTRORM_INTMEM + XSTORM_FUNC_EN_OFFSET(abs_fid),
		enable);
	REG_WR8(bp, BAR_CSTRORM_INTMEM + CSTORM_FUNC_EN_OFFSET(abs_fid),
		enable);
	REG_WR8(bp, BAR_TSTRORM_INTMEM + TSTORM_FUNC_EN_OFFSET(abs_fid),
		enable);
	REG_WR8(bp, BAR_USTRORM_INTMEM + USTORM_FUNC_EN_OFFSET(abs_fid),
		enable);
}