#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_4__ {int addr; } ;
struct TYPE_3__ {int max; } ;
struct nouveau_channel {TYPE_2__ push; TYPE_1__ dma; scalar_t__ user_get_hi; int /*<<< orphan*/  user; scalar_t__ user_get; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int nvif_rd32 (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static inline int
READ_GET(struct nouveau_channel *chan, uint64_t *prev_get, int *timeout)
{
	uint64_t val;

	val = nvif_rd32(&chan->user, chan->user_get);
        if (chan->user_get_hi)
                val |= (uint64_t)nvif_rd32(&chan->user, chan->user_get_hi) << 32;

	/* reset counter as long as GET is still advancing, this is
	 * to avoid misdetecting a GPU lockup if the GPU happens to
	 * just be processing an operation that takes a long time
	 */
	if (val != *prev_get) {
		*prev_get = val;
		*timeout = 0;
	}

	if ((++*timeout & 0xff) == 0) {
		udelay(1);
		if (*timeout > 100000)
			return -EBUSY;
	}

	if (val < chan->push.addr ||
	    val > chan->push.addr + (chan->dma.max << 2))
		return -EINVAL;

	return (val - chan->push.addr) >> 2;
}