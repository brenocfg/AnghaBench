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

__attribute__((used)) static void get_best_ratio(u32 *pnum, u32 *pdenom, u32 max_n, u32 max_d)
{
	u32 a = *pnum;
	u32 b = *pdenom;
	u32 c;
	u32 n[] = {0, 1};
	u32 d[] = {1, 0};
	u32 whole;
	unsigned int i = 1;

	while (b) {
		i ^= 1;
		whole = a / b;
		n[i] += (n[i ^ 1] * whole);
		d[i] += (d[i ^ 1] * whole);
		if ((n[i] > max_n) || (d[i] > max_d)) {
			i ^= 1;
			break;
		}
		c = a - (b * whole);
		a = b;
		b = c;
	}
	*pnum = n[i];
	*pdenom = d[i];
}