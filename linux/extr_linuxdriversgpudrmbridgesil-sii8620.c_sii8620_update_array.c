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

__attribute__((used)) static void sii8620_update_array(u8 *dst, u8 *src, int count)
{
	while (--count >= 0) {
		*src ^= *dst;
		*dst++ ^= *src++;
	}
}