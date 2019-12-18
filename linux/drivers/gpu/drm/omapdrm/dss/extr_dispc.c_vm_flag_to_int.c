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
typedef  enum display_flags { ____Placeholder_display_flags } display_flags ;

/* Variables and functions */

__attribute__((used)) static int vm_flag_to_int(enum display_flags flags, enum display_flags high,
	enum display_flags low)
{
	if (flags & high)
		return 1;
	if (flags & low)
		return -1;
	return 0;
}