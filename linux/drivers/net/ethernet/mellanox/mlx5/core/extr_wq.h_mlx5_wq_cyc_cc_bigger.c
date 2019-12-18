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
typedef  scalar_t__ u16 ;

/* Variables and functions */

__attribute__((used)) static inline int mlx5_wq_cyc_cc_bigger(u16 cc1, u16 cc2)
{
	int equal   = (cc1 == cc2);
	int smaller = 0x8000 & (cc1 - cc2);

	return !equal && !smaller;
}