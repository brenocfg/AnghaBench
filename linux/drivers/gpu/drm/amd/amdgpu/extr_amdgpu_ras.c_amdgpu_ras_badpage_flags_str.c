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

__attribute__((used)) static char *amdgpu_ras_badpage_flags_str(unsigned int flags)
{
	switch (flags) {
	case 0:
		return "R";
	case 1:
		return "P";
	case 2:
	default:
		return "F";
	};
}