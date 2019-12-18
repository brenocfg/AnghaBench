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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */

__attribute__((used)) static void swap_copy24(u8 *dest, const u8 *source, unsigned int bytes)
{
	unsigned int i = 0;

	while (i < bytes - 2) {
		dest[i] = source[i + 2];
		dest[i + 1] = source[i + 1];
		dest[i + 2] = source[i];
		i += 3;
	}
}