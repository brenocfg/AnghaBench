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

__attribute__((used)) static void put_htbl(u8 *p, const u8 *htbl, unsigned int len)
{
	unsigned int i, j;

	for (i = 0; i < len; i += 4)
		for (j = 0; j < 4 && (i + j) < len; ++j)
			p[i + j] = htbl[i + 3 - j];
}