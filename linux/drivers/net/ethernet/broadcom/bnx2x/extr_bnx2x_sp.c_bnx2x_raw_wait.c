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
struct bnx2x_raw_obj {int /*<<< orphan*/  pstate; int /*<<< orphan*/  state; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int bnx2x_state_wait (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bnx2x_raw_wait(struct bnx2x *bp, struct bnx2x_raw_obj *raw)
{
	return bnx2x_state_wait(bp, raw->state, raw->pstate);
}