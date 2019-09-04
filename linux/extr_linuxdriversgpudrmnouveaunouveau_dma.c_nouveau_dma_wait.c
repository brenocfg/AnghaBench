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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_4__ {int free; int cur; int max; int put; scalar_t__ ib_max; } ;
struct TYPE_3__ {int addr; } ;
struct nouveau_channel {TYPE_2__ dma; TYPE_1__ push; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int NOUVEAU_DMA_SKIPS ; 
 int /*<<< orphan*/  OUT_RING (struct nouveau_channel*,int) ; 
 int READ_GET (struct nouveau_channel*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  WRITE_PUT (int) ; 
 int nv50_dma_wait (struct nouveau_channel*,int,int) ; 
 scalar_t__ unlikely (int) ; 

int
nouveau_dma_wait(struct nouveau_channel *chan, int slots, int size)
{
	uint64_t prev_get = 0;
	int cnt = 0, get;

	if (chan->dma.ib_max)
		return nv50_dma_wait(chan, slots, size);

	while (chan->dma.free < size) {
		get = READ_GET(chan, &prev_get, &cnt);
		if (unlikely(get == -EBUSY))
			return -EBUSY;

		/* loop until we have a usable GET pointer.  the value
		 * we read from the GPU may be outside the main ring if
		 * PFIFO is processing a buffer called from the main ring,
		 * discard these values until something sensible is seen.
		 *
		 * the other case we discard GET is while the GPU is fetching
		 * from the SKIPS area, so the code below doesn't have to deal
		 * with some fun corner cases.
		 */
		if (unlikely(get == -EINVAL) || get < NOUVEAU_DMA_SKIPS)
			continue;

		if (get <= chan->dma.cur) {
			/* engine is fetching behind us, or is completely
			 * idle (GET == PUT) so we have free space up until
			 * the end of the push buffer
			 *
			 * we can only hit that path once per call due to
			 * looping back to the beginning of the push buffer,
			 * we'll hit the fetching-ahead-of-us path from that
			 * point on.
			 *
			 * the *one* exception to that rule is if we read
			 * GET==PUT, in which case the below conditional will
			 * always succeed and break us out of the wait loop.
			 */
			chan->dma.free = chan->dma.max - chan->dma.cur;
			if (chan->dma.free >= size)
				break;

			/* not enough space left at the end of the push buffer,
			 * instruct the GPU to jump back to the start right
			 * after processing the currently pending commands.
			 */
			OUT_RING(chan, chan->push.addr | 0x20000000);

			/* wait for GET to depart from the skips area.
			 * prevents writing GET==PUT and causing a race
			 * condition that causes us to think the GPU is
			 * idle when it's not.
			 */
			do {
				get = READ_GET(chan, &prev_get, &cnt);
				if (unlikely(get == -EBUSY))
					return -EBUSY;
				if (unlikely(get == -EINVAL))
					continue;
			} while (get <= NOUVEAU_DMA_SKIPS);
			WRITE_PUT(NOUVEAU_DMA_SKIPS);

			/* we're now submitting commands at the start of
			 * the push buffer.
			 */
			chan->dma.cur  =
			chan->dma.put  = NOUVEAU_DMA_SKIPS;
		}

		/* engine fetching ahead of us, we have space up until the
		 * current GET pointer.  the "- 1" is to ensure there's
		 * space left to emit a jump back to the beginning of the
		 * push buffer if we require it.  we can never get GET == PUT
		 * here, so this is safe.
		 */
		chan->dma.free = get - chan->dma.cur - 1;
	}

	return 0;
}