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
struct ti_st {int reg_status; int /*<<< orphan*/  wait_reg_completion; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void st_reg_completion_cb(void *priv_data, int data)
{
	struct ti_st *lhst = priv_data;

	/* Save registration status for use in ti_st_open() */
	lhst->reg_status = data;
	/* complete the wait in ti_st_open() */
	complete(&lhst->wait_reg_completion);
}