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
struct ms5611_osr {unsigned short rate; } ;

/* Variables and functions */

__attribute__((used)) static const struct ms5611_osr *ms5611_find_osr(int rate,
						const struct ms5611_osr *osr,
						size_t count)
{
	unsigned int r;

	for (r = 0; r < count; r++)
		if ((unsigned short)rate == osr[r].rate)
			break;
	if (r >= count)
		return NULL;
	return &osr[r];
}