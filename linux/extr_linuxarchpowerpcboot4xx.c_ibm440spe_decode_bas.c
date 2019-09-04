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
typedef  int u64 ;
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static u64 ibm440spe_decode_bas(u32 bas)
{
	u64 base = ((u64)(bas & 0xFFE00000u)) << 2;

	/* open coded because I'm paranoid about invalid values */
	switch ((bas >> 4) & 0xFFF) {
	case 0:
		return 0;
	case 0xffc:
		return base + 0x000800000ull;
	case 0xff8:
		return base + 0x001000000ull;
	case 0xff0:
		return base + 0x002000000ull;
	case 0xfe0:
		return base + 0x004000000ull;
	case 0xfc0:
		return base + 0x008000000ull;
	case 0xf80:
		return base + 0x010000000ull;
	case 0xf00:
		return base + 0x020000000ull;
	case 0xe00:
		return base + 0x040000000ull;
	case 0xc00:
		return base + 0x080000000ull;
	case 0x800:
		return base + 0x100000000ull;
	}
	printf("Memory BAS value 0x%08x unsupported !\n", bas);
	return 0;
}