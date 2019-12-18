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
typedef  size_t u32 ;
struct send_context {int flags; scalar_t__ credits; unsigned long fill; unsigned long alloc_free; size_t sr_head; size_t fill_wrap; size_t sr_size; scalar_t__ size; scalar_t__ base_addr; int /*<<< orphan*/  alloc_lock; TYPE_1__* sr; int /*<<< orphan*/ * buffers_allocated; int /*<<< orphan*/  free; } ;
struct TYPE_4__ {scalar_t__ val64; } ;
struct pio_buf {unsigned long sent_at; TYPE_2__ carry; scalar_t__ carry_bytes; scalar_t__ qw_written; scalar_t__ end; scalar_t__ start; struct send_context* sc; void* arg; int /*<<< orphan*/  cb; } ;
typedef  int /*<<< orphan*/  pio_release_cb ;
struct TYPE_3__ {struct pio_buf pbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECOMM ; 
 struct pio_buf* ERR_PTR (int /*<<< orphan*/ ) ; 
 size_t PIO_BLOCK_SIZE ; 
 void* READ_ONCE (int /*<<< orphan*/ ) ; 
 int SCF_ENABLED ; 
 unsigned long dwords_to_blocks (size_t) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  sc_release_update (struct send_context*) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  this_cpu_inc (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

struct pio_buf *sc_buffer_alloc(struct send_context *sc, u32 dw_len,
				pio_release_cb cb, void *arg)
{
	struct pio_buf *pbuf = NULL;
	unsigned long flags;
	unsigned long avail;
	unsigned long blocks = dwords_to_blocks(dw_len);
	u32 fill_wrap;
	int trycount = 0;
	u32 head, next;

	spin_lock_irqsave(&sc->alloc_lock, flags);
	if (!(sc->flags & SCF_ENABLED)) {
		spin_unlock_irqrestore(&sc->alloc_lock, flags);
		return ERR_PTR(-ECOMM);
	}

retry:
	avail = (unsigned long)sc->credits - (sc->fill - sc->alloc_free);
	if (blocks > avail) {
		/* not enough room */
		if (unlikely(trycount))	{ /* already tried to get more room */
			spin_unlock_irqrestore(&sc->alloc_lock, flags);
			goto done;
		}
		/* copy from receiver cache line and recalculate */
		sc->alloc_free = READ_ONCE(sc->free);
		avail =
			(unsigned long)sc->credits -
			(sc->fill - sc->alloc_free);
		if (blocks > avail) {
			/* still no room, actively update */
			sc_release_update(sc);
			sc->alloc_free = READ_ONCE(sc->free);
			trycount++;
			goto retry;
		}
	}

	/* there is enough room */

	preempt_disable();
	this_cpu_inc(*sc->buffers_allocated);

	/* read this once */
	head = sc->sr_head;

	/* "allocate" the buffer */
	sc->fill += blocks;
	fill_wrap = sc->fill_wrap;
	sc->fill_wrap += blocks;
	if (sc->fill_wrap >= sc->credits)
		sc->fill_wrap = sc->fill_wrap - sc->credits;

	/*
	 * Fill the parts that the releaser looks at before moving the head.
	 * The only necessary piece is the sent_at field.  The credits
	 * we have just allocated cannot have been returned yet, so the
	 * cb and arg will not be looked at for a "while".  Put them
	 * on this side of the memory barrier anyway.
	 */
	pbuf = &sc->sr[head].pbuf;
	pbuf->sent_at = sc->fill;
	pbuf->cb = cb;
	pbuf->arg = arg;
	pbuf->sc = sc;	/* could be filled in at sc->sr init time */
	/* make sure this is in memory before updating the head */

	/* calculate next head index, do not store */
	next = head + 1;
	if (next >= sc->sr_size)
		next = 0;
	/*
	 * update the head - must be last! - the releaser can look at fields
	 * in pbuf once we move the head
	 */
	smp_wmb();
	sc->sr_head = next;
	spin_unlock_irqrestore(&sc->alloc_lock, flags);

	/* finish filling in the buffer outside the lock */
	pbuf->start = sc->base_addr + fill_wrap * PIO_BLOCK_SIZE;
	pbuf->end = sc->base_addr + sc->size;
	pbuf->qw_written = 0;
	pbuf->carry_bytes = 0;
	pbuf->carry.val64 = 0;
done:
	return pbuf;
}