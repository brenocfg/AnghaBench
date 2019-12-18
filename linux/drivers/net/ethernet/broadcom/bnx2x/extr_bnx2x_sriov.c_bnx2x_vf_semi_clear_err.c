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
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSEM_REG_VFPF_ERR_NUM ; 
 int /*<<< orphan*/  REG_WR (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TSEM_REG_VFPF_ERR_NUM ; 
 int /*<<< orphan*/  USEM_REG_VFPF_ERR_NUM ; 
 int /*<<< orphan*/  XSEM_REG_VFPF_ERR_NUM ; 

__attribute__((used)) static void bnx2x_vf_semi_clear_err(struct bnx2x *bp, u8 abs_vfid)
{
	REG_WR(bp, TSEM_REG_VFPF_ERR_NUM, abs_vfid);
	REG_WR(bp, USEM_REG_VFPF_ERR_NUM, abs_vfid);
	REG_WR(bp, CSEM_REG_VFPF_ERR_NUM, abs_vfid);
	REG_WR(bp, XSEM_REG_VFPF_ERR_NUM, abs_vfid);
}