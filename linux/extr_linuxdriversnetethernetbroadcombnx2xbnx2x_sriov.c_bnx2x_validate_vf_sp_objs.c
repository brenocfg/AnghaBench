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
struct bnx2x_virtf {int dummy; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*) ; 
 int /*<<< orphan*/  BNX2X_MSG_IOV ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  bnx2x_leading_vfq (struct bnx2x_virtf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sp_initialized ; 

__attribute__((used)) static bool bnx2x_validate_vf_sp_objs(struct bnx2x *bp,
				       struct bnx2x_virtf *vf,
				       bool print_err)
{
	if (!bnx2x_leading_vfq(vf, sp_initialized)) {
		if (print_err)
			BNX2X_ERR("Slowpath objects not yet initialized!\n");
		else
			DP(BNX2X_MSG_IOV, "Slowpath objects not yet initialized!\n");
		return false;
	}
	return true;
}