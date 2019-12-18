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
 unsigned short I2C_CLIENT_END ; 

__attribute__((used)) static unsigned int pvr2_copy_i2c_addr_list(
	unsigned short *dst, const unsigned char *src,
	unsigned int dst_max)
{
	unsigned int cnt = 0;
	if (!src) return 0;
	while (src[cnt] && (cnt + 1) < dst_max) {
		dst[cnt] = src[cnt];
		cnt++;
	}
	dst[cnt] = I2C_CLIENT_END;
	return cnt;
}