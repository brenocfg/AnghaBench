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
typedef  size_t u32 ;

/* Variables and functions */

__attribute__((used)) static void register_format(u32 format, u32 formats[], u32 *nb_of_formats)
{
	u32 i;
	bool found = false;

	for (i = 0; i < *nb_of_formats; i++) {
		if (format == formats[i]) {
			found = true;
			break;
		}
	}

	if (!found)
		formats[(*nb_of_formats)++] = format;
}