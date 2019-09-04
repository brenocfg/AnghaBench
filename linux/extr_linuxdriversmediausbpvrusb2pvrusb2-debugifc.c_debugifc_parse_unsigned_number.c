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
typedef  int u32 ;

/* Variables and functions */
 int EINVAL ; 
 int hex_to_bin (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int debugifc_parse_unsigned_number(const char *buf,unsigned int count,
					  u32 *num_ptr)
{
	u32 result = 0;
	int radix = 10;
	if ((count >= 2) && (buf[0] == '0') &&
	    ((buf[1] == 'x') || (buf[1] == 'X'))) {
		radix = 16;
		count -= 2;
		buf += 2;
	} else if ((count >= 1) && (buf[0] == '0')) {
		radix = 8;
	}

	while (count--) {
		int val = hex_to_bin(*buf++);
		if (val < 0 || val >= radix)
			return -EINVAL;
		result *= radix;
		result += val;
	}
	*num_ptr = result;
	return 0;
}