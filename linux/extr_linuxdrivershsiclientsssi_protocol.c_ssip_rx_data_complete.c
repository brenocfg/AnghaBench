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
struct ssi_protocol {int /*<<< orphan*/  rx_wd; } ;
struct sk_buff {int dummy; } ;
struct hsi_msg {scalar_t__ status; struct sk_buff* context; struct hsi_client* cl; } ;
struct hsi_client {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 scalar_t__ HSI_STATUS_ERROR ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct ssi_protocol* hsi_client_drvdata (struct hsi_client*) ; 
 int /*<<< orphan*/  hsi_free_msg (struct hsi_msg*) ; 
 int /*<<< orphan*/  ssip_error (struct hsi_client*) ; 
 int /*<<< orphan*/  ssip_free_data (struct hsi_msg*) ; 
 int /*<<< orphan*/  ssip_pn_rx (struct sk_buff*) ; 

__attribute__((used)) static void ssip_rx_data_complete(struct hsi_msg *msg)
{
	struct hsi_client *cl = msg->cl;
	struct ssi_protocol *ssi = hsi_client_drvdata(cl);
	struct sk_buff *skb;

	if (msg->status == HSI_STATUS_ERROR) {
		dev_err(&cl->device, "RX data error\n");
		ssip_free_data(msg);
		ssip_error(cl);
		return;
	}
	del_timer(&ssi->rx_wd); /* FIXME: Revisit */
	skb = msg->context;
	ssip_pn_rx(skb);
	hsi_free_msg(msg);
}