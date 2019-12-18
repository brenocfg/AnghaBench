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
struct b43legacy_dmaring {int nr_slots; int used_slots; int /*<<< orphan*/  rx_buffersize; TYPE_1__* dev; } ;
struct b43legacy_dmadesc_meta {int /*<<< orphan*/  skb; int /*<<< orphan*/  dmaaddr; } ;
struct b43legacy_dmadesc32 {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  wl; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  b43legacyerr (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb () ; 
 struct b43legacy_dmadesc32* op32_idx2desc (struct b43legacy_dmaring*,int,struct b43legacy_dmadesc_meta**) ; 
 int setup_rx_descbuffer (struct b43legacy_dmaring*,struct b43legacy_dmadesc32*,struct b43legacy_dmadesc_meta*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unmap_descbuffer (struct b43legacy_dmaring*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int alloc_initial_descbuffers(struct b43legacy_dmaring *ring)
{
	int i;
	int err = -ENOMEM;
	struct b43legacy_dmadesc32 *desc;
	struct b43legacy_dmadesc_meta *meta;

	for (i = 0; i < ring->nr_slots; i++) {
		desc = op32_idx2desc(ring, i, &meta);

		err = setup_rx_descbuffer(ring, desc, meta, GFP_KERNEL);
		if (err) {
			b43legacyerr(ring->dev->wl,
			       "Failed to allocate initial descbuffers\n");
			goto err_unwind;
		}
	}
	mb(); /* all descbuffer setup before next line */
	ring->used_slots = ring->nr_slots;
	err = 0;
out:
	return err;

err_unwind:
	for (i--; i >= 0; i--) {
		desc = op32_idx2desc(ring, i, &meta);

		unmap_descbuffer(ring, meta->dmaaddr, ring->rx_buffersize, 0);
		dev_kfree_skb(meta->skb);
	}
	goto out;
}