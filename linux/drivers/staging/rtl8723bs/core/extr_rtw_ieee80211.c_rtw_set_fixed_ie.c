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
typedef  unsigned char u8 ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (void*,void*,unsigned int) ; 

u8 *rtw_set_fixed_ie(unsigned char *pbuf, unsigned int len, unsigned char *source,
				unsigned int *frlen)
{
	memcpy((void *)pbuf, (void *)source, len);
	*frlen = *frlen + len;
	return pbuf + len;
}