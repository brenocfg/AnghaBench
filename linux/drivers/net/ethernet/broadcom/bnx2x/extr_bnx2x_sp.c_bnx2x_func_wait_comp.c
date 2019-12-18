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
struct bnx2x_func_sp_obj {int /*<<< orphan*/  pending; } ;
struct bnx2x {int dummy; } ;
typedef  enum bnx2x_func_cmd { ____Placeholder_bnx2x_func_cmd } bnx2x_func_cmd ;

/* Variables and functions */
 int bnx2x_state_wait (struct bnx2x*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bnx2x_func_wait_comp(struct bnx2x *bp,
				struct bnx2x_func_sp_obj *o,
				enum bnx2x_func_cmd cmd)
{
	return bnx2x_state_wait(bp, cmd, &o->pending);
}