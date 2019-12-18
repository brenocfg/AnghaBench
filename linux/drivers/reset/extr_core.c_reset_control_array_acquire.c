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
struct reset_control_array {unsigned int num_rstcs; int /*<<< orphan*/ * rstc; } ;

/* Variables and functions */
 int reset_control_acquire (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_release (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int reset_control_array_acquire(struct reset_control_array *resets)
{
	unsigned int i;
	int err;

	for (i = 0; i < resets->num_rstcs; i++) {
		err = reset_control_acquire(resets->rstc[i]);
		if (err < 0)
			goto release;
	}

	return 0;

release:
	while (i--)
		reset_control_release(resets->rstc[i]);

	return err;
}