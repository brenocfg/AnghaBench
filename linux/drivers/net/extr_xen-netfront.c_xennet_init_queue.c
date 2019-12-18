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
struct netfront_queue {int id; int /*<<< orphan*/  gref_tx_head; int /*<<< orphan*/  gref_rx_head; void** grant_rx_ref; int /*<<< orphan*/ ** rx_skbs; int /*<<< orphan*/ ** grant_tx_page; void** grant_tx_ref; int /*<<< orphan*/ * tx_skbs; scalar_t__ tx_skb_freelist; int /*<<< orphan*/  name; TYPE_2__* info; int /*<<< orphan*/  rx_refill_timer; int /*<<< orphan*/  rx_lock; int /*<<< orphan*/  tx_lock; } ;
struct TYPE_4__ {TYPE_1__* xbdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  nodename; } ;

/* Variables and functions */
 int ENOMEM ; 
 void* GRANT_INVALID_REF ; 
 unsigned short NET_RX_RING_SIZE ; 
 unsigned short NET_TX_RING_SIZE ; 
 scalar_t__ gnttab_alloc_grant_references (unsigned short,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gnttab_free_grant_references (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_alert (char*) ; 
 int /*<<< orphan*/  rx_refill_timeout ; 
 int /*<<< orphan*/  skb_entry_set_link (int /*<<< orphan*/ *,unsigned short) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 char* strrchr (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xennet_init_queue(struct netfront_queue *queue)
{
	unsigned short i;
	int err = 0;
	char *devid;

	spin_lock_init(&queue->tx_lock);
	spin_lock_init(&queue->rx_lock);

	timer_setup(&queue->rx_refill_timer, rx_refill_timeout, 0);

	devid = strrchr(queue->info->xbdev->nodename, '/') + 1;
	snprintf(queue->name, sizeof(queue->name), "vif%s-q%u",
		 devid, queue->id);

	/* Initialise tx_skbs as a free chain containing every entry. */
	queue->tx_skb_freelist = 0;
	for (i = 0; i < NET_TX_RING_SIZE; i++) {
		skb_entry_set_link(&queue->tx_skbs[i], i+1);
		queue->grant_tx_ref[i] = GRANT_INVALID_REF;
		queue->grant_tx_page[i] = NULL;
	}

	/* Clear out rx_skbs */
	for (i = 0; i < NET_RX_RING_SIZE; i++) {
		queue->rx_skbs[i] = NULL;
		queue->grant_rx_ref[i] = GRANT_INVALID_REF;
	}

	/* A grant for every tx ring slot */
	if (gnttab_alloc_grant_references(NET_TX_RING_SIZE,
					  &queue->gref_tx_head) < 0) {
		pr_alert("can't alloc tx grant refs\n");
		err = -ENOMEM;
		goto exit;
	}

	/* A grant for every rx ring slot */
	if (gnttab_alloc_grant_references(NET_RX_RING_SIZE,
					  &queue->gref_rx_head) < 0) {
		pr_alert("can't alloc rx grant refs\n");
		err = -ENOMEM;
		goto exit_free_tx;
	}

	return 0;

 exit_free_tx:
	gnttab_free_grant_references(queue->gref_tx_head);
 exit:
	return err;
}