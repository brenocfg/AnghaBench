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
typedef  scalar_t__ uint16_t ;
struct msm_ringbuffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OUT_RING (struct msm_ringbuffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PKT4 (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  adreno_wait_ring (struct msm_ringbuffer*,scalar_t__) ; 

__attribute__((used)) static inline void
OUT_PKT4(struct msm_ringbuffer *ring, uint16_t regindx, uint16_t cnt)
{
	adreno_wait_ring(ring, cnt + 1);
	OUT_RING(ring, PKT4(regindx, cnt));
}