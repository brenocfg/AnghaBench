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
struct microread_i2c_phy {int /*<<< orphan*/  hdev; struct i2c_client* i2c_dev; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_RISING ; 
 int /*<<< orphan*/  LLC_SHDLC_NAME ; 
 int /*<<< orphan*/  MICROREAD_I2C_DRIVER_NAME ; 
 int /*<<< orphan*/  MICROREAD_I2C_FRAME_HEADROOM ; 
 int /*<<< orphan*/  MICROREAD_I2C_FRAME_TAILROOM ; 
 int /*<<< orphan*/  MICROREAD_I2C_LLC_MAX_PAYLOAD ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,struct i2c_client*) ; 
 struct microread_i2c_phy* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct microread_i2c_phy*) ; 
 int /*<<< orphan*/  i2c_phy_ops ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct microread_i2c_phy*) ; 
 int /*<<< orphan*/  microread_i2c_irq_thread_fn ; 
 int microread_probe (struct microread_i2c_phy*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfc_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  nfc_info (int /*<<< orphan*/ *,char*) ; 
 int request_threaded_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct microread_i2c_phy*) ; 

__attribute__((used)) static int microread_i2c_probe(struct i2c_client *client,
			       const struct i2c_device_id *id)
{
	struct microread_i2c_phy *phy;
	int r;

	dev_dbg(&client->dev, "client %p\n", client);

	phy = devm_kzalloc(&client->dev, sizeof(struct microread_i2c_phy),
			   GFP_KERNEL);
	if (!phy)
		return -ENOMEM;

	i2c_set_clientdata(client, phy);
	phy->i2c_dev = client;

	r = request_threaded_irq(client->irq, NULL, microread_i2c_irq_thread_fn,
				 IRQF_TRIGGER_RISING | IRQF_ONESHOT,
				 MICROREAD_I2C_DRIVER_NAME, phy);
	if (r) {
		nfc_err(&client->dev, "Unable to register IRQ handler\n");
		return r;
	}

	r = microread_probe(phy, &i2c_phy_ops, LLC_SHDLC_NAME,
			    MICROREAD_I2C_FRAME_HEADROOM,
			    MICROREAD_I2C_FRAME_TAILROOM,
			    MICROREAD_I2C_LLC_MAX_PAYLOAD, &phy->hdev);
	if (r < 0)
		goto err_irq;

	nfc_info(&client->dev, "Probed\n");

	return 0;

err_irq:
	free_irq(client->irq, phy);

	return r;
}