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
struct wf_fcu_priv {int /*<<< orphan*/  fan_list; struct i2c_client* i2c; int /*<<< orphan*/  lock; int /*<<< orphan*/  ref; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct wf_fcu_priv*) ; 
 int /*<<< orphan*/  kfree (struct wf_fcu_priv*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct wf_fcu_priv* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  wf_fcu_default_fans (struct wf_fcu_priv*) ; 
 scalar_t__ wf_fcu_init_chip (struct wf_fcu_priv*) ; 
 int /*<<< orphan*/  wf_fcu_lookup_fans (struct wf_fcu_priv*) ; 

__attribute__((used)) static int wf_fcu_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	struct wf_fcu_priv *pv;

	pv = kzalloc(sizeof(*pv), GFP_KERNEL);
	if (!pv)
		return -ENOMEM;

	kref_init(&pv->ref);
	mutex_init(&pv->lock);
	INIT_LIST_HEAD(&pv->fan_list);
	pv->i2c = client;

	/*
	 * First we must start the FCU which will query the
	 * shift value to apply to RPMs
	 */
	if (wf_fcu_init_chip(pv)) {
		pr_err("wf_fcu: Initialization failed !\n");
		kfree(pv);
		return -ENXIO;
	}

	/* First lookup fans in the device-tree */
	wf_fcu_lookup_fans(pv);

	/*
	 * Older machines don't have the device-tree entries
	 * we are looking for, just hard code the list
	 */
	if (list_empty(&pv->fan_list))
		wf_fcu_default_fans(pv);

	/* Still no fans ? FAIL */
	if (list_empty(&pv->fan_list)) {
		pr_err("wf_fcu: Failed to find fans for your machine\n");
		kfree(pv);
		return -ENODEV;
	}

	dev_set_drvdata(&client->dev, pv);

	return 0;
}