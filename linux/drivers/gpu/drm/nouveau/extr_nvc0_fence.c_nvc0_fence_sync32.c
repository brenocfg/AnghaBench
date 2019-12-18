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
struct nouveau_channel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEGIN_NVC0 (struct nouveau_channel*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FIRE_RING (struct nouveau_channel*) ; 
 int /*<<< orphan*/  NV84_SUBCHAN_SEMAPHORE_ADDRESS_HIGH ; 
 int NV84_SUBCHAN_SEMAPHORE_TRIGGER_ACQUIRE_GEQUAL ; 
 int NVC0_SUBCHAN_SEMAPHORE_TRIGGER_YIELD ; 
 int /*<<< orphan*/  OUT_RING (struct nouveau_channel*,int) ; 
 int RING_SPACE (struct nouveau_channel*,int) ; 
 int lower_32_bits (int /*<<< orphan*/ ) ; 
 int upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nvc0_fence_sync32(struct nouveau_channel *chan, u64 virtual, u32 sequence)
{
	int ret = RING_SPACE(chan, 5);
	if (ret == 0) {
		BEGIN_NVC0(chan, 0, NV84_SUBCHAN_SEMAPHORE_ADDRESS_HIGH, 4);
		OUT_RING  (chan, upper_32_bits(virtual));
		OUT_RING  (chan, lower_32_bits(virtual));
		OUT_RING  (chan, sequence);
		OUT_RING  (chan, NV84_SUBCHAN_SEMAPHORE_TRIGGER_ACQUIRE_GEQUAL |
				 NVC0_SUBCHAN_SEMAPHORE_TRIGGER_YIELD);
		FIRE_RING (chan);
	}
	return ret;
}