#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* u8 ;
struct TYPE_8__ {int* model; } ;
struct TYPE_6__ {int /*<<< orphan*/  tag; } ;
struct TYPE_5__ {scalar_t__* plant; int /*<<< orphan*/  tag; } ;
struct qeth_node_desc {TYPE_4__ nd3; TYPE_2__ nd2; TYPE_1__ nd1; } ;
struct qeth_cmd_buffer {scalar_t__ data; } ;
struct TYPE_7__ {int is_vm_nic; int use_v1_blkt; void* cula; void* unit_addr2; void* chpid; } ;
struct qeth_card {TYPE_3__ info; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 scalar_t__* _ascebc ; 
 int /*<<< orphan*/  qeth_notify_cmd (struct qeth_cmd_buffer*,int) ; 
 int /*<<< orphan*/  qeth_put_cmd (struct qeth_cmd_buffer*) ; 

__attribute__((used)) static void qeth_read_conf_data_cb(struct qeth_card *card,
				   struct qeth_cmd_buffer *iob,
				   unsigned int data_length)
{
	struct qeth_node_desc *nd = (struct qeth_node_desc *) iob->data;
	int rc = 0;
	u8 *tag;

	QETH_CARD_TEXT(card, 2, "cfgunit");

	if (data_length < sizeof(*nd)) {
		rc = -EINVAL;
		goto out;
	}

	card->info.is_vm_nic = nd->nd1.plant[0] == _ascebc['V'] &&
			       nd->nd1.plant[1] == _ascebc['M'];
	tag = (u8 *)&nd->nd1.tag;
	card->info.chpid = tag[0];
	card->info.unit_addr2 = tag[1];

	tag = (u8 *)&nd->nd2.tag;
	card->info.cula = tag[1];

	card->info.use_v1_blkt = nd->nd3.model[0] == 0xF0 &&
				 nd->nd3.model[1] == 0xF0 &&
				 nd->nd3.model[2] >= 0xF1 &&
				 nd->nd3.model[2] <= 0xF4;

out:
	qeth_notify_cmd(iob, rc);
	qeth_put_cmd(iob);
}