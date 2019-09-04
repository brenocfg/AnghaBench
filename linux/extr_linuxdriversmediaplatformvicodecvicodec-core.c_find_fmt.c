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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (scalar_t__*) ; 
 scalar_t__* pixfmts_yuv ; 

__attribute__((used)) static u32 find_fmt(u32 fmt)
{
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(pixfmts_yuv); i++)
		if (pixfmts_yuv[i] == fmt)
			return fmt;
	return pixfmts_yuv[0];
}