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
struct lcs_card {int /*<<< orphan*/  lancmd_waiters; int /*<<< orphan*/  ipm_list; int /*<<< orphan*/  mask_lock; int /*<<< orphan*/  ipm_lock; int /*<<< orphan*/  lock; int /*<<< orphan*/  wait_q; scalar_t__ tx_emitted; int /*<<< orphan*/ * tx_buffer; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEV_STATE_DOWN ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LCS_DBF_HEX (int,int /*<<< orphan*/ ,struct lcs_card**,int) ; 
 int /*<<< orphan*/  LCS_DBF_TEXT (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lcs_setup_read (struct lcs_card*) ; 
 int /*<<< orphan*/  lcs_setup_write (struct lcs_card*) ; 
 int /*<<< orphan*/  setup ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
lcs_setup_card(struct lcs_card *card)
{
	LCS_DBF_TEXT(2, setup, "initcard");
	LCS_DBF_HEX(2, setup, &card, sizeof(void*));

	lcs_setup_read(card);
	lcs_setup_write(card);
	/* Set cards initial state. */
	card->state = DEV_STATE_DOWN;
	card->tx_buffer = NULL;
	card->tx_emitted = 0;

	init_waitqueue_head(&card->wait_q);
	spin_lock_init(&card->lock);
	spin_lock_init(&card->ipm_lock);
	spin_lock_init(&card->mask_lock);
#ifdef CONFIG_IP_MULTICAST
	INIT_LIST_HEAD(&card->ipm_list);
#endif
	INIT_LIST_HEAD(&card->lancmd_waiters);
}