#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct qeth_sbp_state_change {int entry_length; int num_entries; } ;
struct qeth_sbp_port_entry {int dummy; } ;
struct TYPE_4__ {struct qeth_sbp_state_change state_change; } ;
struct TYPE_5__ {TYPE_1__ data; } ;
struct TYPE_6__ {TYPE_2__ sbp; } ;
struct qeth_ipa_cmd {TYPE_3__ data; } ;
struct qeth_card {int /*<<< orphan*/  event_wq; } ;
struct qeth_bridge_state_data {int /*<<< orphan*/  worker; int /*<<< orphan*/  qports; struct qeth_card* card; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 int /*<<< orphan*/  QETH_CARD_TEXT_ (struct qeth_card*,int,char*,int) ; 
 struct qeth_bridge_state_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct qeth_sbp_state_change*,int) ; 
 int /*<<< orphan*/  qeth_bridge_state_change_worker ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qeth_bridge_state_change(struct qeth_card *card,
					struct qeth_ipa_cmd *cmd)
{
	struct qeth_sbp_state_change *qports =
		 &cmd->data.sbp.data.state_change;
	struct qeth_bridge_state_data *data;
	int extrasize;

	QETH_CARD_TEXT(card, 2, "brstchng");
	if (qports->entry_length != sizeof(struct qeth_sbp_port_entry)) {
		QETH_CARD_TEXT_(card, 2, "BPsz%04x", qports->entry_length);
		return;
	}
	extrasize = sizeof(struct qeth_sbp_port_entry) * qports->num_entries;
	data = kzalloc(sizeof(struct qeth_bridge_state_data) + extrasize,
		GFP_ATOMIC);
	if (!data) {
		QETH_CARD_TEXT(card, 2, "BPSalloc");
		return;
	}
	INIT_WORK(&data->worker, qeth_bridge_state_change_worker);
	data->card = card;
	memcpy(&data->qports, qports,
			sizeof(struct qeth_sbp_state_change) + extrasize);
	queue_work(card->event_wq, &data->worker);
}