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
struct drm_printer {int dummy; } ;

/* Variables and functions */
 int RANGE (int const*,int) ; 
 int /*<<< orphan*/  drm_printf (struct drm_printer*,char*,int,int) ; 

__attribute__((used)) static void a6xx_show_registers(const u32 *registers, u32 *data, size_t count,
		struct drm_printer *p)
{
	int i, index = 0;

	if (!data)
		return;

	for (i = 0; i < count; i += 2) {
		u32 count = RANGE(registers, i);
		u32 offset = registers[i];
		int j;

		for (j = 0; j < count; index++, offset++, j++) {
			if (data[index] == 0xdeafbead)
				continue;

			drm_printf(p, "  - { offset: 0x%06x, value: 0x%08x }\n",
				offset << 2, data[index]);
		}
	}
}