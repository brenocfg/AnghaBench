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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct msm_ringbuffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CP_REG_TO_MEM ; 
 int /*<<< orphan*/  OUT_PKT7 (struct msm_ringbuffer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OUT_RING (struct msm_ringbuffer*,int) ; 
 int lower_32_bits (int /*<<< orphan*/ ) ; 
 int upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void get_stats_counter(struct msm_ringbuffer *ring, u32 counter,
		u64 iova)
{
	OUT_PKT7(ring, CP_REG_TO_MEM, 3);
	OUT_RING(ring, counter | (1 << 30) | (2 << 18));
	OUT_RING(ring, lower_32_bits(iova));
	OUT_RING(ring, upper_32_bits(iova));
}