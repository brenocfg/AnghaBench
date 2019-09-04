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
 int /*<<< orphan*/  CHIP_IS_E1 (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_clp_reset_done (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int bnx2x_init_shmem (struct bnx2x*) ; 

__attribute__((used)) static int bnx2x_reset_mcp_comp(struct bnx2x *bp, u32 magic_val)
{
	int rc = bnx2x_init_shmem(bp);

	/* Restore the `magic' bit value */
	if (!CHIP_IS_E1(bp))
		bnx2x_clp_reset_done(bp, magic_val);

	return rc;
}