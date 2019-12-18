#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct b43_wldev {TYPE_1__* dev; } ;
struct b43_pio_txqueue {int rev; unsigned int index; int buffer_size; int /*<<< orphan*/  packets_list; struct b43_pio_txpacket* packets; int /*<<< orphan*/  free_packet_slots; scalar_t__ mmio_base; struct b43_wldev* dev; } ;
struct b43_pio_txpacket {unsigned int index; int /*<<< orphan*/  list; struct b43_pio_txqueue* queue; } ;
struct TYPE_2__ {int core_rev; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct b43_pio_txpacket*) ; 
 int /*<<< orphan*/  B43_PIO_MAX_NR_TXPACKETS ; 
 int /*<<< orphan*/  B43_PIO_TXQBUFSIZE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int b43_piotx_read16 (struct b43_pio_txqueue*,int /*<<< orphan*/ ) ; 
 scalar_t__ index_to_pioqueue_base (struct b43_wldev*,unsigned int) ; 
 struct b43_pio_txqueue* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pio_txqueue_offset (struct b43_wldev*) ; 

__attribute__((used)) static struct b43_pio_txqueue *b43_setup_pioqueue_tx(struct b43_wldev *dev,
						     unsigned int index)
{
	struct b43_pio_txqueue *q;
	struct b43_pio_txpacket *p;
	unsigned int i;

	q = kzalloc(sizeof(*q), GFP_KERNEL);
	if (!q)
		return NULL;
	q->dev = dev;
	q->rev = dev->dev->core_rev;
	q->mmio_base = index_to_pioqueue_base(dev, index) +
		       pio_txqueue_offset(dev);
	q->index = index;

	q->free_packet_slots = B43_PIO_MAX_NR_TXPACKETS;
	if (q->rev >= 8) {
		q->buffer_size = 1920; //FIXME this constant is wrong.
	} else {
		q->buffer_size = b43_piotx_read16(q, B43_PIO_TXQBUFSIZE);
		q->buffer_size -= 80;
	}

	INIT_LIST_HEAD(&q->packets_list);
	for (i = 0; i < ARRAY_SIZE(q->packets); i++) {
		p = &(q->packets[i]);
		INIT_LIST_HEAD(&p->list);
		p->index = i;
		p->queue = q;
		list_add(&p->list, &q->packets_list);
	}

	return q;
}