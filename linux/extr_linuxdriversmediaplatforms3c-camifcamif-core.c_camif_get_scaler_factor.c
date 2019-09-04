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
 int EINVAL ; 

__attribute__((used)) static int camif_get_scaler_factor(u32 src, u32 tar, u32 *ratio, u32 *shift)
{
	unsigned int sh = 6;

	if (src >= 64 * tar)
		return -EINVAL;

	while (sh--) {
		unsigned int tmp = 1 << sh;
		if (src >= tar * tmp) {
			*shift = sh, *ratio = tmp;
			return 0;
		}
	}
	*shift = 0, *ratio = 1;
	return 0;
}