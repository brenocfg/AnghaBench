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

/* Variables and functions */
 int /*<<< orphan*/  i2c_trace_msg_key ; 
 int /*<<< orphan*/  static_branch_inc (int /*<<< orphan*/ *) ; 

int i2c_transfer_trace_reg(void)
{
	static_branch_inc(&i2c_trace_msg_key);
	return 0;
}