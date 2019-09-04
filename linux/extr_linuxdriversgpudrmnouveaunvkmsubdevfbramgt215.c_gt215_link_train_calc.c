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
typedef  int u32 ;
struct gt215_ltrain {int r_100720; int r_1111e0; int r_111400; } ;

/* Variables and functions */
 int max (int,int) ; 
 int min (int,int) ; 

__attribute__((used)) static void
gt215_link_train_calc(u32 *vals, struct gt215_ltrain *train)
{
	int i, lo, hi;
	u8 median[8], bins[4] = {0, 0, 0, 0}, bin = 0, qty = 0;

	for (i = 0; i < 8; i++) {
		for (lo = 0; lo < 0x40; lo++) {
			if (!(vals[lo] & 0x80000000))
				continue;
			if (vals[lo] & (0x101 << i))
				break;
		}

		if (lo == 0x40)
			return;

		for (hi = lo + 1; hi < 0x40; hi++) {
			if (!(vals[lo] & 0x80000000))
				continue;
			if (!(vals[hi] & (0x101 << i))) {
				hi--;
				break;
			}
		}

		median[i] = ((hi - lo) >> 1) + lo;
		bins[(median[i] & 0xf0) >> 4]++;
		median[i] += 0x30;
	}

	/* Find the best value for 0x1111e0 */
	for (i = 0; i < 4; i++) {
		if (bins[i] > qty) {
			bin = i + 3;
			qty = bins[i];
		}
	}

	train->r_100720 = 0;
	for (i = 0; i < 8; i++) {
		median[i] = max(median[i], (u8) (bin << 4));
		median[i] = min(median[i], (u8) ((bin << 4) | 0xf));

		train->r_100720 |= ((median[i] & 0x0f) << (i << 2));
	}

	train->r_1111e0 = 0x02000000 | (bin * 0x101);
	train->r_111400 = 0x0;
}