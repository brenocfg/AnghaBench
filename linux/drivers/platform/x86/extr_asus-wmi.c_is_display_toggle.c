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

__attribute__((used)) static int is_display_toggle(int code)
{
	/* display toggle keys */
	if ((code >= 0x61 && code <= 0x67) ||
	    (code >= 0x8c && code <= 0x93) ||
	    (code >= 0xa0 && code <= 0xa7) ||
	    (code >= 0xd0 && code <= 0xd5))
		return 1;

	return 0;
}