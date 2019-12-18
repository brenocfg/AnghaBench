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
struct asus_laptop {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  PEGA_ACC_CLAMP ; 
 int PEGA_ACC_RETRIES ; 
 int abs (int) ; 
 int /*<<< orphan*/  acpi_evaluate_integer (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,unsigned long long*) ; 
 int clamp_val (short,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pega_acc_axis(struct asus_laptop *asus, int curr, char *method)
{
	int i, delta;
	unsigned long long val;
	for (i = 0; i < PEGA_ACC_RETRIES; i++) {
		acpi_evaluate_integer(asus->handle, method, NULL, &val);

		/* The output is noisy.  From reading the ASL
		 * dissassembly, timeout errors are returned with 1's
		 * in the high word, and the lack of locking around
		 * thei hi/lo byte reads means that a transition
		 * between (for example) -1 and 0 could be read as
		 * 0xff00 or 0x00ff. */
		delta = abs(curr - (short)val);
		if (delta < 128 && !(val & ~0xffff))
			break;
	}
	return clamp_val((short)val, -PEGA_ACC_CLAMP, PEGA_ACC_CLAMP);
}