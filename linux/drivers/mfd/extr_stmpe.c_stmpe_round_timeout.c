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
 int ARRAY_SIZE (int*) ; 
 int EINVAL ; 
 int* stmpe_autosleep_delay ; 

__attribute__((used)) static int stmpe_round_timeout(int timeout)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(stmpe_autosleep_delay); i++) {
		if (stmpe_autosleep_delay[i] >= timeout)
			return i;
	}

	/*
	 * requests for delays longer than supported should not return the
	 * longest supported delay
	 */
	return -EINVAL;
}