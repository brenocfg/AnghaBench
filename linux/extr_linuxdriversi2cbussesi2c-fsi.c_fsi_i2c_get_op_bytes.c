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

__attribute__((used)) static int fsi_i2c_get_op_bytes(int op_bytes)
{
	/* fsi is limited to max 4 byte aligned ops */
	if (op_bytes > 4)
		return 4;
	else if (op_bytes == 3)
		return 2;
	return op_bytes;
}