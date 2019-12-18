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
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 scalar_t__ div64_u64 (unsigned long long,scalar_t__) ; 
 scalar_t__ get_unaligned_be32 (int /*<<< orphan*/ *) ; 
 unsigned long long get_unaligned_be64 (scalar_t__*) ; 

__attribute__((used)) static u64 occ_get_powr_avg(u64 *accum, u32 *samples)
{
	u64 divisor = get_unaligned_be32(samples);

	return (divisor == 0) ? 0 :
		div64_u64(get_unaligned_be64(accum) * 1000000ULL, divisor);
}