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
struct TYPE_2__ {void** inuse; int /*<<< orphan*/  inuse_cnt; } ;
struct rio_channel {int /*<<< orphan*/  lock; TYPE_1__ rx_ring; } ;

/* Variables and functions */
 int EINVAL ; 
 int RIOCM_RX_RING_SIZE ; 
 int /*<<< orphan*/  kfree (void*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int riocm_ch_free_rxbuf(struct rio_channel *ch, void *buf)
{
	int i, ret = -EINVAL;

	spin_lock_bh(&ch->lock);

	for (i = 0; i < RIOCM_RX_RING_SIZE; i++) {
		if (ch->rx_ring.inuse[i] == buf) {
			ch->rx_ring.inuse[i] = NULL;
			ch->rx_ring.inuse_cnt--;
			ret = 0;
			break;
		}
	}

	spin_unlock_bh(&ch->lock);

	if (!ret)
		kfree(buf);

	return ret;
}