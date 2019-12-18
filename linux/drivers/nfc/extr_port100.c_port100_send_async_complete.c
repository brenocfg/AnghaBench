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
struct sk_buff {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct port100_cmd {int status; int /*<<< orphan*/  complete_cb_context; int /*<<< orphan*/  (* complete_cb ) (struct port100*,int /*<<< orphan*/ ,struct sk_buff*) ;struct sk_buff* resp; struct sk_buff* req; } ;
struct port100 {struct port100_cmd* cmd; } ;

/* Variables and functions */
 struct sk_buff* ERR_PTR (int) ; 
 int /*<<< orphan*/  PORT100_FRAME_HEADER_LEN ; 
 scalar_t__ PORT100_FRAME_TAIL_LEN ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree (struct port100_cmd*) ; 
 int /*<<< orphan*/  port100_rx_frame_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct port100*,int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  stub2 (struct port100*,int /*<<< orphan*/ ,struct sk_buff*) ; 

__attribute__((used)) static void port100_send_async_complete(struct port100 *dev)
{
	struct port100_cmd *cmd = dev->cmd;
	int status = cmd->status;

	struct sk_buff *req = cmd->req;
	struct sk_buff *resp = cmd->resp;

	dev_kfree_skb(req);

	dev->cmd = NULL;

	if (status < 0) {
		cmd->complete_cb(dev, cmd->complete_cb_context,
				 ERR_PTR(status));
		dev_kfree_skb(resp);
		goto done;
	}

	skb_put(resp, port100_rx_frame_size(resp->data));
	skb_pull(resp, PORT100_FRAME_HEADER_LEN);
	skb_trim(resp, resp->len - PORT100_FRAME_TAIL_LEN);

	cmd->complete_cb(dev, cmd->complete_cb_context, resp);

done:
	kfree(cmd);
}