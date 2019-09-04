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
typedef  scalar_t__ u8 ;
struct bnx2x_fastpath {scalar_t__ index; int /*<<< orphan*/  bp; } ;

/* Variables and functions */
 scalar_t__ BP_L_ID (int /*<<< orphan*/ ) ; 
 scalar_t__ CHIP_IS_E1x (int /*<<< orphan*/ ) ; 
 scalar_t__ bnx2x_fp_igu_sb_id (struct bnx2x_fastpath*) ; 

__attribute__((used)) static u8 bnx2x_fp_cl_id(struct bnx2x_fastpath *fp)
{
	if (CHIP_IS_E1x(fp->bp))
		return BP_L_ID(fp->bp) + fp->index;
	else	/* We want Client ID to be the same as IGU SB ID for 57712 */
		return bnx2x_fp_igu_sb_id(fp);
}