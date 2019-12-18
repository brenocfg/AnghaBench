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
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;

/* Variables and functions */
 int /*<<< orphan*/  div64_u64 (int,int) ; 

__attribute__((used)) static inline u32 ti_iodelay_compute_dpe(u16 period, u16 ref, u16 delay,
					 u16 delay_m)
{
	u64 m, d;

	/* Handle overflow conditions */
	m = 10 * (u64)period * (u64)ref;
	d = 2 * (u64)delay * (u64)delay_m;

	/* Truncate result back to 32 bits */
	return div64_u64(m, d);
}