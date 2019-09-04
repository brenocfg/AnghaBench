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

void amdgpu_calculate_u_and_p(u32 i, u32 r_c, u32 p_b,
			      u32 *p, u32 *u)
{
	u32 b_c = 0;
	u32 i_c;
	u32 tmp;

	i_c = (i * r_c) / 100;
	tmp = i_c >> p_b;

	while (tmp) {
		b_c++;
		tmp >>= 1;
	}

	*u = (b_c + 1) / 2;
	*p = i_c / (1 << (2 * (*u)));
}