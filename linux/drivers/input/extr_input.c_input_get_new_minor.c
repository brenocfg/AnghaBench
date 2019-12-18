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
 int /*<<< orphan*/  GFP_KERNEL ; 
 int INPUT_FIRST_DYNAMIC_DEV ; 
 int INPUT_MAX_CHAR_DEVICES ; 
 int ida_simple_get (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_ida ; 

int input_get_new_minor(int legacy_base, unsigned int legacy_num,
			bool allow_dynamic)
{
	/*
	 * This function should be called from input handler's ->connect()
	 * methods, which are serialized with input_mutex, so no additional
	 * locking is needed here.
	 */
	if (legacy_base >= 0) {
		int minor = ida_simple_get(&input_ida,
					   legacy_base,
					   legacy_base + legacy_num,
					   GFP_KERNEL);
		if (minor >= 0 || !allow_dynamic)
			return minor;
	}

	return ida_simple_get(&input_ida,
			      INPUT_FIRST_DYNAMIC_DEV, INPUT_MAX_CHAR_DEVICES,
			      GFP_KERNEL);
}