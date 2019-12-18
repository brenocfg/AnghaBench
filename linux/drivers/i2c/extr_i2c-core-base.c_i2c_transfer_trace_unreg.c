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
 int /*<<< orphan*/  static_branch_dec (int /*<<< orphan*/ *) ; 

void i2c_transfer_trace_unreg(void)
{
	static_branch_dec(&i2c_trace_msg_key);
}