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
typedef  size_t u8 ;
typedef  int s32 ;

/* Variables and functions */
 int ARRAY_SIZE (int const*) ; 

__attribute__((used)) static bool is_rate_ht40(s32 rate, u8 *mcs, bool *sgi)
{
	static const s32 ht40[] = { 13500, 27000, 40500, 54000,
		81000, 108000, 121500, 135000,
		150000
	};
	u8 i;

	for (i = 0; i < ARRAY_SIZE(ht40); i++) {
		if (rate == ht40[i]) {
			if (i == ARRAY_SIZE(ht40) - 1)
				/* last rate uses sgi */
				*sgi = true;
			else
				*sgi = false;

			*mcs = i;
			return true;
		}
	}

	return false;
}