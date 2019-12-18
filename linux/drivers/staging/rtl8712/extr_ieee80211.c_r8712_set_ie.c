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
typedef  scalar_t__ uint ;
typedef  scalar_t__ u8 ;
typedef  scalar_t__ sint ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (void*,void*,scalar_t__) ; 

u8 *r8712_set_ie(u8 *pbuf, sint index, uint len, u8 *source, uint *frlen)
{
	*pbuf = (u8)index;
	*(pbuf + 1) = (u8)len;
	if (len > 0)
		memcpy((void *)(pbuf + 2), (void *)source, len);
	*frlen = *frlen + (len + 2);
	return pbuf + len + 2;
}