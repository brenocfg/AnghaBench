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
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct b43legacy_wldev {int /*<<< orphan*/  wl; TYPE_2__* dev; } ;
struct b43legacy_pioqueue {int need_workarounds; scalar_t__ tx_devq_size; scalar_t__ mmio_base; int /*<<< orphan*/  txtask; int /*<<< orphan*/  txrunning; int /*<<< orphan*/  txqueue; int /*<<< orphan*/  txfree; struct b43legacy_wldev* dev; } ;
struct TYPE_3__ {int revision; } ;
struct TYPE_4__ {TYPE_1__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43legacy_MACCTL_BE ; 
 int /*<<< orphan*/  B43legacy_MMIO_MACCTL ; 
 scalar_t__ B43legacy_PIO_TXQADJUST ; 
 scalar_t__ B43legacy_PIO_TXQBUFSIZE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ b43legacy_read16 (struct b43legacy_wldev*,scalar_t__) ; 
 int /*<<< orphan*/  b43legacy_read32 (struct b43legacy_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43legacy_write32 (struct b43legacy_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43legacyerr (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  kfree (struct b43legacy_pioqueue*) ; 
 struct b43legacy_pioqueue* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup_txqueues (struct b43legacy_pioqueue*) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  tx_tasklet ; 

__attribute__((used)) static
struct b43legacy_pioqueue *b43legacy_setup_pioqueue(struct b43legacy_wldev *dev,
						    u16 pio_mmio_base)
{
	struct b43legacy_pioqueue *queue;
	u32 value;
	u16 qsize;

	queue = kzalloc(sizeof(*queue), GFP_KERNEL);
	if (!queue)
		goto out;

	queue->dev = dev;
	queue->mmio_base = pio_mmio_base;
	queue->need_workarounds = (dev->dev->id.revision < 3);

	INIT_LIST_HEAD(&queue->txfree);
	INIT_LIST_HEAD(&queue->txqueue);
	INIT_LIST_HEAD(&queue->txrunning);
	tasklet_init(&queue->txtask, tx_tasklet,
		     (unsigned long)queue);

	value = b43legacy_read32(dev, B43legacy_MMIO_MACCTL);
	value &= ~B43legacy_MACCTL_BE;
	b43legacy_write32(dev, B43legacy_MMIO_MACCTL, value);

	qsize = b43legacy_read16(dev, queue->mmio_base
				 + B43legacy_PIO_TXQBUFSIZE);
	if (qsize == 0) {
		b43legacyerr(dev->wl, "This card does not support PIO "
		       "operation mode. Please use DMA mode "
		       "(module parameter pio=0).\n");
		goto err_freequeue;
	}
	if (qsize <= B43legacy_PIO_TXQADJUST) {
		b43legacyerr(dev->wl, "PIO tx device-queue too small (%u)\n",
		       qsize);
		goto err_freequeue;
	}
	qsize -= B43legacy_PIO_TXQADJUST;
	queue->tx_devq_size = qsize;

	setup_txqueues(queue);

out:
	return queue;

err_freequeue:
	kfree(queue);
	queue = NULL;
	goto out;
}