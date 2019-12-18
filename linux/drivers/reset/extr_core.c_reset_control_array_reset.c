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
struct reset_control_array {int num_rstcs; int /*<<< orphan*/ * rstc; } ;

/* Variables and functions */
 int reset_control_reset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int reset_control_array_reset(struct reset_control_array *resets)
{
	int ret, i;

	for (i = 0; i < resets->num_rstcs; i++) {
		ret = reset_control_reset(resets->rstc[i]);
		if (ret)
			return ret;
	}

	return 0;
}