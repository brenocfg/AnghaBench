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
typedef  int s32 ;

/* Variables and functions */
 int VPD_FAIL ; 
 int VPD_OK ; 

__attribute__((used)) static int vpd_decode_len(const s32 max_len, const u8 *in,
			  s32 *length, s32 *decoded_len)
{
	u8 more;
	int i = 0;

	if (!length || !decoded_len)
		return VPD_FAIL;

	*length = 0;
	do {
		if (i >= max_len)
			return VPD_FAIL;

		more = in[i] & 0x80;
		*length <<= 7;
		*length |= in[i] & 0x7f;
		++i;
	} while (more);

	*decoded_len = i;

	return VPD_OK;
}