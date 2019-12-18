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
struct fst_port_info {size_t index; scalar_t__ start; scalar_t__ txipos; scalar_t__ txpos; struct fst_card_info* card; } ;
struct fst_card_info {int /*<<< orphan*/  card_lock; } ;

/* Variables and functions */
 unsigned short ABORTTX ; 
 int /*<<< orphan*/  DBG_CMD ; 
 unsigned short FST_RDW (struct fst_card_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FST_WRW (struct fst_card_info*,int /*<<< orphan*/ ,unsigned short) ; 
 unsigned short NAK ; 
 unsigned short STARTPORT ; 
 int /*<<< orphan*/  dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ ** portMailbox ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  schedule_timeout_uninterruptible (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
fst_issue_cmd(struct fst_port_info *port, unsigned short cmd)
{
	struct fst_card_info *card;
	unsigned short mbval;
	unsigned long flags;
	int safety;

	card = port->card;
	spin_lock_irqsave(&card->card_lock, flags);
	mbval = FST_RDW(card, portMailbox[port->index][0]);

	safety = 0;
	/* Wait for any previous command to complete */
	while (mbval > NAK) {
		spin_unlock_irqrestore(&card->card_lock, flags);
		schedule_timeout_uninterruptible(1);
		spin_lock_irqsave(&card->card_lock, flags);

		if (++safety > 2000) {
			pr_err("Mailbox safety timeout\n");
			break;
		}

		mbval = FST_RDW(card, portMailbox[port->index][0]);
	}
	if (safety > 0) {
		dbg(DBG_CMD, "Mailbox clear after %d jiffies\n", safety);
	}
	if (mbval == NAK) {
		dbg(DBG_CMD, "issue_cmd: previous command was NAK'd\n");
	}

	FST_WRW(card, portMailbox[port->index][0], cmd);

	if (cmd == ABORTTX || cmd == STARTPORT) {
		port->txpos = 0;
		port->txipos = 0;
		port->start = 0;
	}

	spin_unlock_irqrestore(&card->card_lock, flags);
}