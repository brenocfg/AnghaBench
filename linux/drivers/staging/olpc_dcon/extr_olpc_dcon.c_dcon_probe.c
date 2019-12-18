#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct TYPE_9__ {int priority; int /*<<< orphan*/  notifier_call; } ;
struct dcon_priv {int bl_val; TYPE_1__ reboot_nb; int /*<<< orphan*/ * bl_dev; int /*<<< orphan*/  fbinfo; int /*<<< orphan*/  switch_source; int /*<<< orphan*/  waitq; struct i2c_client* client; } ;
struct TYPE_11__ {int brightness; } ;
struct TYPE_10__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DCON_IRQ ; 
 int /*<<< orphan*/  DCON_REG_BRIGHT ; 
 int EIO ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_notifier_chain_register (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * backlight_device_register (char*,int /*<<< orphan*/ *,struct dcon_priv*,int /*<<< orphan*/ *,TYPE_7__*) ; 
 int /*<<< orphan*/  dcon_bl_ops ; 
 TYPE_7__ dcon_bl_props ; 
 TYPE_2__* dcon_device ; 
 int /*<<< orphan*/ * dcon_device_files ; 
 int dcon_hw_init (struct dcon_priv*,int) ; 
 int /*<<< orphan*/  dcon_panic_nb ; 
 int dcon_read (struct dcon_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dcon_reboot_notify ; 
 int /*<<< orphan*/  dcon_source_switch ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int device_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct dcon_priv*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct dcon_priv*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct dcon_priv*) ; 
 struct dcon_priv* kzalloc (int,int /*<<< orphan*/ ) ; 
 int num_registered_fb ; 
 int /*<<< orphan*/  panic_notifier_list ; 
 int /*<<< orphan*/  pdata ; 
 int platform_device_add (TYPE_2__*) ; 
 TYPE_2__* platform_device_alloc (char*,int) ; 
 int /*<<< orphan*/  platform_device_unregister (TYPE_2__*) ; 
 int /*<<< orphan*/  platform_set_drvdata (TYPE_2__*,struct dcon_priv*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  register_reboot_notifier (TYPE_1__*) ; 
 int /*<<< orphan*/ * registered_fb ; 

__attribute__((used)) static int dcon_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	struct dcon_priv *dcon;
	int rc, i, j;

	if (!pdata)
		return -ENXIO;

	dcon = kzalloc(sizeof(*dcon), GFP_KERNEL);
	if (!dcon)
		return -ENOMEM;

	dcon->client = client;
	init_waitqueue_head(&dcon->waitq);
	INIT_WORK(&dcon->switch_source, dcon_source_switch);
	dcon->reboot_nb.notifier_call = dcon_reboot_notify;
	dcon->reboot_nb.priority = -1;

	i2c_set_clientdata(client, dcon);

	if (num_registered_fb < 1) {
		dev_err(&client->dev, "DCON driver requires a registered fb\n");
		rc = -EIO;
		goto einit;
	}
	dcon->fbinfo = registered_fb[0];

	rc = dcon_hw_init(dcon, 1);
	if (rc)
		goto einit;

	/* Add the DCON device */

	dcon_device = platform_device_alloc("dcon", -1);

	if (!dcon_device) {
		pr_err("Unable to create the DCON device\n");
		rc = -ENOMEM;
		goto eirq;
	}
	rc = platform_device_add(dcon_device);
	platform_set_drvdata(dcon_device, dcon);

	if (rc) {
		pr_err("Unable to add the DCON device\n");
		goto edev;
	}

	for (i = 0; i < ARRAY_SIZE(dcon_device_files); i++) {
		rc = device_create_file(&dcon_device->dev,
					&dcon_device_files[i]);
		if (rc) {
			dev_err(&dcon_device->dev, "Cannot create sysfs file\n");
			goto ecreate;
		}
	}

	dcon->bl_val = dcon_read(dcon, DCON_REG_BRIGHT) & 0x0F;

	/* Add the backlight device for the DCON */
	dcon_bl_props.brightness = dcon->bl_val;
	dcon->bl_dev = backlight_device_register("dcon-bl", &dcon_device->dev,
						 dcon, &dcon_bl_ops,
						 &dcon_bl_props);
	if (IS_ERR(dcon->bl_dev)) {
		dev_err(&client->dev, "cannot register backlight dev (%ld)\n",
			PTR_ERR(dcon->bl_dev));
		dcon->bl_dev = NULL;
	}

	register_reboot_notifier(&dcon->reboot_nb);
	atomic_notifier_chain_register(&panic_notifier_list, &dcon_panic_nb);

	return 0;

 ecreate:
	for (j = 0; j < i; j++)
		device_remove_file(&dcon_device->dev, &dcon_device_files[j]);
 edev:
	platform_device_unregister(dcon_device);
	dcon_device = NULL;
 eirq:
	free_irq(DCON_IRQ, dcon);
 einit:
	kfree(dcon);
	return rc;
}