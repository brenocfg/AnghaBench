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

__attribute__((used)) static u32 encoded_size(u32 size)
{
	switch (size) {
	case   4 * 1024: return 0x1;
	case   8 * 1024: return 0x2;
	case  16 * 1024: return 0x3;
	case  32 * 1024: return 0x4;
	case  64 * 1024: return 0x5;
	case 128 * 1024: return 0x6;
	case 256 * 1024: return 0x7;
	case 512 * 1024: return 0x8;
	case   1 * 1024 * 1024: return 0x9;
	case   2 * 1024 * 1024: return 0xa;
	}
	return 0x1;	/* if invalid, go with the minimum size */
}