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

__attribute__((used)) static int get_encoded_page_size(int pg_sz)
{
	/* Max size is 256M 4096 << 16 */
	int i = 0;
	for (; i < 17; i++)
		if (pg_sz == (4096 << i))
			break;
	return i;
}