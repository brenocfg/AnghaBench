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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int len; int /*<<< orphan*/  data; } ;
struct pn533_frame_ops {int /*<<< orphan*/  (* tx_frame_finish ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* tx_update_payload_len ) (int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* tx_frame_init ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  tx_tail_len; int /*<<< orphan*/  tx_header_len; } ;
struct pn533 {struct pn533_frame_ops* ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  skb_push (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pn533_build_cmd_frame(struct pn533 *dev, u8 cmd_code,
				  struct sk_buff *skb)
{
	/* payload is already there, just update datalen */
	int payload_len = skb->len;
	struct pn533_frame_ops *ops = dev->ops;


	skb_push(skb, ops->tx_header_len);
	skb_put(skb, ops->tx_tail_len);

	ops->tx_frame_init(skb->data, cmd_code);
	ops->tx_update_payload_len(skb->data, payload_len);
	ops->tx_frame_finish(skb->data);
}