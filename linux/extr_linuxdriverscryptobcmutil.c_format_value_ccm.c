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
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

void format_value_ccm(unsigned int val, u8 *buf, u8 len)
{
	int i;

	/* First clear full output buffer */
	memset(buf, 0, len);

	/* Then, starting from right side, fill in with data */
	for (i = 0; i < len; i++) {
		buf[len - i - 1] = (val >> (8 * i)) & 0xff;
		if (i >= 3)
			break;  /* Only handle up to 32 bits of 'val' */
	}
}