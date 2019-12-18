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
struct atyfb_par {int mem_refresh_rate; } ;

/* Variables and functions */
 int ARRAY_SIZE (int const*) ; 
 scalar_t__ M64_HAS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XL_MEM ; 

__attribute__((used)) static void aty_calc_mem_refresh(struct atyfb_par *par, int xclk)
{
	static const int ragepro_tbl[] = {
		44, 50, 55, 66, 75, 80, 100
	};
	static const int ragexl_tbl[] = {
		50, 66, 75, 83, 90, 95, 100, 105,
		110, 115, 120, 125, 133, 143, 166
	};
	const int *refresh_tbl;
	int i, size;

	if (M64_HAS(XL_MEM)) {
		refresh_tbl = ragexl_tbl;
		size = ARRAY_SIZE(ragexl_tbl);
	} else {
		refresh_tbl = ragepro_tbl;
		size = ARRAY_SIZE(ragepro_tbl);
	}

	for (i = 0; i < size; i++) {
		if (xclk < refresh_tbl[i])
			break;
	}
	par->mem_refresh_rate = i;
}