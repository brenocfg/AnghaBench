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

__attribute__((used)) static int syndrome_to_qword_code(int syndrome_code)
{
	if (syndrome_code < 128)
		syndrome_code += 16;
	else if (syndrome_code < 128 + 9)
		syndrome_code -= (128 - 7);
	else if (syndrome_code < (128 + 9 + 3))
		syndrome_code -= (128 + 9 - 4);
	else
		syndrome_code -= (128 + 9 + 3);
	return syndrome_code;
}