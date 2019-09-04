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
typedef  int u64 ;

/* Variables and functions */

__attribute__((used)) static u8 nfp_bytemask(int width, u64 addr)
{
	if (width == 8)
		return 0xff;
	else if (width == 4)
		return 0x0f << (addr & 4);
	else if (width == 2)
		return 0x03 << (addr & 6);
	else if (width == 1)
		return 0x01 << (addr & 7);
	else
		return 0;
}