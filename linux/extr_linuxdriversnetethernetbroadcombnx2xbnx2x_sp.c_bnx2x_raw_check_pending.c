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

/* Variables and functions */
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool bnx2x_raw_check_pending(struct bnx2x_raw_obj *o)
{
	return !!test_bit(o->state, o->pstate);
}