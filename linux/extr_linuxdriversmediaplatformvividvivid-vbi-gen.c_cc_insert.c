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
typedef  int u8 ;

/* Variables and functions */

__attribute__((used)) static void cc_insert(u8 *cc, u8 ch)
{
	unsigned tot = 0;
	unsigned i;

	for (i = 0; i < 7; i++) {
		cc[2 * i] = cc[2 * i + 1] = (ch & (1 << i)) ? 1 : 0;
		tot += cc[2 * i];
	}
	cc[14] = cc[15] = !(tot & 1);
}