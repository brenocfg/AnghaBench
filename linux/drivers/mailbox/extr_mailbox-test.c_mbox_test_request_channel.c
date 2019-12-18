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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct mbox_client {int tx_block; int knows_txdone; int tx_tout; int /*<<< orphan*/  tx_done; int /*<<< orphan*/  tx_prepare; int /*<<< orphan*/  rx_callback; int /*<<< orphan*/ * dev; } ;
struct mbox_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct mbox_chan* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct mbox_chan*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,char const*) ; 
 struct mbox_client* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct mbox_chan* mbox_request_channel_byname (struct mbox_client*,char const*) ; 
 int /*<<< orphan*/  mbox_test_message_sent ; 
 int /*<<< orphan*/  mbox_test_prepare_message ; 
 int /*<<< orphan*/  mbox_test_receive_message ; 

__attribute__((used)) static struct mbox_chan *
mbox_test_request_channel(struct platform_device *pdev, const char *name)
{
	struct mbox_client *client;
	struct mbox_chan *channel;

	client = devm_kzalloc(&pdev->dev, sizeof(*client), GFP_KERNEL);
	if (!client)
		return ERR_PTR(-ENOMEM);

	client->dev		= &pdev->dev;
	client->rx_callback	= mbox_test_receive_message;
	client->tx_prepare	= mbox_test_prepare_message;
	client->tx_done		= mbox_test_message_sent;
	client->tx_block	= true;
	client->knows_txdone	= false;
	client->tx_tout		= 500;

	channel = mbox_request_channel_byname(client, name);
	if (IS_ERR(channel)) {
		dev_warn(&pdev->dev, "Failed to request %s channel\n", name);
		return NULL;
	}

	return channel;
}