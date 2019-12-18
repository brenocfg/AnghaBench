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
typedef  int u16 ;
struct sk_buff {scalar_t__ data; } ;
struct port100_tg_comm_rf_cmd {void* recv_timeout; void* send_timeout; void* guard_time; } ;
struct port100_cb_arg {void* complete_arg; int /*<<< orphan*/  complete_cb; } ;
struct port100 {int dummy; } ;
struct nfc_digital_dev {int dummy; } ;
typedef  int /*<<< orphan*/  nfc_digital_cmd_complete_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PORT100_CMD_TG_COMM_RF ; 
 void* cpu_to_le16 (int) ; 
 struct port100_cb_arg* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct port100_tg_comm_rf_cmd*,int /*<<< orphan*/ ,int) ; 
 struct port100* nfc_digital_get_drvdata (struct nfc_digital_dev*) ; 
 int port100_send_cmd_async (struct port100*,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,struct port100_cb_arg*) ; 
 int /*<<< orphan*/  port100_tg_comm_rf_complete ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int) ; 

__attribute__((used)) static int port100_tg_send_cmd(struct nfc_digital_dev *ddev,
			       struct sk_buff *skb, u16 timeout,
			       nfc_digital_cmd_complete_t cb, void *arg)
{
	struct port100 *dev = nfc_digital_get_drvdata(ddev);
	struct port100_tg_comm_rf_cmd *hdr;
	struct port100_cb_arg *cb_arg;

	cb_arg = kzalloc(sizeof(struct port100_cb_arg), GFP_KERNEL);
	if (!cb_arg)
		return -ENOMEM;

	cb_arg->complete_cb = cb;
	cb_arg->complete_arg = arg;

	skb_push(skb, sizeof(struct port100_tg_comm_rf_cmd));

	hdr = (struct port100_tg_comm_rf_cmd *)skb->data;

	memset(hdr, 0, sizeof(struct port100_tg_comm_rf_cmd));
	hdr->guard_time = cpu_to_le16(500);
	hdr->send_timeout = cpu_to_le16(0xFFFF);
	hdr->recv_timeout = cpu_to_le16(timeout);

	return port100_send_cmd_async(dev, PORT100_CMD_TG_COMM_RF, skb,
				      port100_tg_comm_rf_complete, cb_arg);
}