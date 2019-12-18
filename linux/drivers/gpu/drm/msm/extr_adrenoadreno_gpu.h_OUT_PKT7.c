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
typedef  int uint8_t ;
typedef  int uint16_t ;
struct msm_ringbuffer {int dummy; } ;

/* Variables and functions */
 int CP_TYPE7_PKT ; 
 int /*<<< orphan*/  OUT_RING (struct msm_ringbuffer*,int) ; 
 int PM4_PARITY (int) ; 
 int /*<<< orphan*/  adreno_wait_ring (struct msm_ringbuffer*,int) ; 

__attribute__((used)) static inline void
OUT_PKT7(struct msm_ringbuffer *ring, uint8_t opcode, uint16_t cnt)
{
	adreno_wait_ring(ring, cnt + 1);
	OUT_RING(ring, CP_TYPE7_PKT | (cnt << 0) | (PM4_PARITY(cnt) << 15) |
		((opcode & 0x7F) << 16) | (PM4_PARITY(opcode) << 23));
}