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
struct qeth_ipacmd_addr_change_entry {int dummy; } ;
struct qeth_ipacmd_addr_change {int lost_event_mask; int num_entries; } ;
struct TYPE_4__ {int return_code; } ;
struct TYPE_3__ {struct qeth_ipacmd_addr_change addrchange; } ;
struct qeth_ipa_cmd {TYPE_2__ hdr; TYPE_1__ data; } ;
struct qeth_card {int /*<<< orphan*/  event_wq; } ;
struct qeth_bridge_host_data {int /*<<< orphan*/  worker; int /*<<< orphan*/  hostevs; struct qeth_card* card; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 int /*<<< orphan*/  QETH_CARD_TEXT_ (struct qeth_card*,int,char*,int) ; 
 struct qeth_bridge_host_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct qeth_ipacmd_addr_change*,int) ; 
 int /*<<< orphan*/  qeth_bridge_host_event_worker ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qeth_bridge_host_event(struct qeth_card *card,
					struct qeth_ipa_cmd *cmd)
{
	struct qeth_ipacmd_addr_change *hostevs =
		 &cmd->data.addrchange;
	struct qeth_bridge_host_data *data;
	int extrasize;

	QETH_CARD_TEXT(card, 2, "brhostev");
	if (cmd->hdr.return_code != 0x0000) {
		if (cmd->hdr.return_code == 0x0010) {
			if (hostevs->lost_event_mask == 0x00)
				hostevs->lost_event_mask = 0xff;
		} else {
			QETH_CARD_TEXT_(card, 2, "BPHe%04x",
				cmd->hdr.return_code);
			return;
		}
	}
	extrasize = sizeof(struct qeth_ipacmd_addr_change_entry) *
						hostevs->num_entries;
	data = kzalloc(sizeof(struct qeth_bridge_host_data) + extrasize,
		GFP_ATOMIC);
	if (!data) {
		QETH_CARD_TEXT(card, 2, "BPHalloc");
		return;
	}
	INIT_WORK(&data->worker, qeth_bridge_host_event_worker);
	data->card = card;
	memcpy(&data->hostevs, hostevs,
			sizeof(struct qeth_ipacmd_addr_change) + extrasize);
	queue_work(card->event_wq, &data->worker);
}