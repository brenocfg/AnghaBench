#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct device {int dummy; } ;
struct TYPE_2__ {int tx_block; struct device* dev; } ;
struct cmdq_client {int /*<<< orphan*/  chan; TYPE_1__ client; scalar_t__ pkt_cnt; int /*<<< orphan*/  timer; int /*<<< orphan*/  lock; scalar_t__ timeout_ms; } ;

/* Variables and functions */
 scalar_t__ CMDQ_NO_TIMEOUT ; 
 scalar_t__ ENOMEM ; 
 struct cmdq_client* ERR_PTR (long) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 long PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmdq_client_timeout ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  kfree (struct cmdq_client*) ; 
 struct cmdq_client* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbox_request_channel (TYPE_1__*,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct cmdq_client *cmdq_mbox_create(struct device *dev, int index, u32 timeout)
{
	struct cmdq_client *client;

	client = kzalloc(sizeof(*client), GFP_KERNEL);
	if (!client)
		return (struct cmdq_client *)-ENOMEM;

	client->timeout_ms = timeout;
	if (timeout != CMDQ_NO_TIMEOUT) {
		spin_lock_init(&client->lock);
		timer_setup(&client->timer, cmdq_client_timeout, 0);
	}
	client->pkt_cnt = 0;
	client->client.dev = dev;
	client->client.tx_block = false;
	client->chan = mbox_request_channel(&client->client, index);

	if (IS_ERR(client->chan)) {
		long err;

		dev_err(dev, "failed to request channel\n");
		err = PTR_ERR(client->chan);
		kfree(client);

		return ERR_PTR(err);
	}

	return client;
}