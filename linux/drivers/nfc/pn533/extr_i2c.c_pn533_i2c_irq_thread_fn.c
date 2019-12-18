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
struct sk_buff {int dummy; } ;
struct pn533_i2c_phy {int hard_fault; int /*<<< orphan*/  priv; int /*<<< orphan*/  aborted; struct i2c_client* i2c_dev; } ;
struct i2c_client {int irq; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int EBADMSG ; 
 int EBUSY ; 
 int ENOMEM ; 
 int EREMOTEIO ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int pn533_i2c_read (struct pn533_i2c_phy*,struct sk_buff**) ; 
 int /*<<< orphan*/  pn533_recv_frame (int /*<<< orphan*/ ,struct sk_buff*,int) ; 

__attribute__((used)) static irqreturn_t pn533_i2c_irq_thread_fn(int irq, void *data)
{
	struct pn533_i2c_phy *phy = data;
	struct i2c_client *client;
	struct sk_buff *skb = NULL;
	int r;

	if (!phy || irq != phy->i2c_dev->irq) {
		WARN_ON_ONCE(1);
		return IRQ_NONE;
	}

	client = phy->i2c_dev;
	dev_dbg(&client->dev, "IRQ\n");

	if (phy->hard_fault != 0)
		return IRQ_HANDLED;

	r = pn533_i2c_read(phy, &skb);
	if (r == -EREMOTEIO) {
		phy->hard_fault = r;

		pn533_recv_frame(phy->priv, NULL, -EREMOTEIO);

		return IRQ_HANDLED;
	} else if ((r == -ENOMEM) || (r == -EBADMSG) || (r == -EBUSY)) {
		return IRQ_HANDLED;
	}

	if (!phy->aborted)
		pn533_recv_frame(phy->priv, skb, 0);

	return IRQ_HANDLED;
}