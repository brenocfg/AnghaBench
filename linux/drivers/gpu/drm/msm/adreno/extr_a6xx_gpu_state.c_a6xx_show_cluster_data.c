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
 int A6XX_NUM_CONTEXTS ; 
 int RANGE (int const*,int) ; 
 int /*<<< orphan*/  drm_printf (struct drm_printer*,char*,int,...) ; 

__attribute__((used)) static void a6xx_show_cluster_data(const u32 *registers, int size, u32 *data,
		struct drm_printer *p)
{
	int ctx, index = 0;

	for (ctx = 0; ctx < A6XX_NUM_CONTEXTS; ctx++) {
		int j;

		drm_printf(p, "    - context: %d\n", ctx);

		for (j = 0; j < size; j += 2) {
			u32 count = RANGE(registers, j);
			u32 offset = registers[j];
			int k;

			for (k = 0; k < count; index++, offset++, k++) {
				if (data[index] == 0xdeafbead)
					continue;

				drm_printf(p, "      - { offset: 0x%06x, value: 0x%08x }\n",
					offset << 2, data[index]);
			}
		}
	}
}