#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char const* name; struct wf_lm87_sensor* priv; int /*<<< orphan*/ * ops; } ;
struct wf_lm87_sensor {TYPE_2__ sens; struct i2c_client* i2c; } ;
struct i2c_device_id {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  of_node; } ;
struct i2c_client {TYPE_1__ dev; } ;
struct device_node {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct wf_lm87_sensor*) ; 
 int /*<<< orphan*/  kfree (struct wf_lm87_sensor*) ; 
 struct wf_lm87_sensor* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct device_node* of_get_next_child (int /*<<< orphan*/ ,struct device_node*) ; 
 char* of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  pr_warning (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strstr (char const*,char*) ; 
 int /*<<< orphan*/  wf_lm87_ops ; 
 int wf_register_sensor (TYPE_2__*) ; 

__attribute__((used)) static int wf_lm87_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{	
	struct wf_lm87_sensor *lm;
	const char *name = NULL, *loc;
	struct device_node *np = NULL;
	int rc;

	/*
	 * The lm87 contains a whole pile of sensors, additionally,
	 * the Xserve G5 has several lm87's. However, for now we only
	 * care about the internal temperature sensor
	 */
	while ((np = of_get_next_child(client->dev.of_node, np)) != NULL) {
		if (strcmp(np->name, "int-temp"))
			continue;
		loc = of_get_property(np, "location", NULL);
		if (!loc)
			continue;
		if (strstr(loc, "DIMM"))
			name = "dimms-temp";
		else if (strstr(loc, "Processors"))
			name = "between-cpus-temp";
		if (name) {
			of_node_put(np);
			break;
		}
	}
	if (!name) {
		pr_warning("wf_lm87: Unsupported sensor %pOF\n",
			   client->dev.of_node);
		return -ENODEV;
	}

	lm = kzalloc(sizeof(struct wf_lm87_sensor), GFP_KERNEL);
	if (lm == NULL)
		return -ENODEV;

	lm->i2c = client;
	lm->sens.name = name;
	lm->sens.ops = &wf_lm87_ops;
	lm->sens.priv = lm;
	i2c_set_clientdata(client, lm);

	rc = wf_register_sensor(&lm->sens);
	if (rc)
		kfree(lm);
	return rc;
}