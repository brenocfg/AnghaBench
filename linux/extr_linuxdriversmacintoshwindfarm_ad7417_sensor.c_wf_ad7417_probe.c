#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct wf_ad7417_priv {int cpu; struct mpu_data const* mpu; struct i2c_client* i2c; int /*<<< orphan*/  lock; int /*<<< orphan*/  ref; } ;
struct mpu_data {int dummy; } ;
struct i2c_device_id {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  of_node; } ;
struct i2c_client {TYPE_1__ dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_1__*,struct wf_ad7417_priv*) ; 
 int /*<<< orphan*/  dev_warn (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct wf_ad7417_priv* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 char* of_get_property (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,char const*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 
 int /*<<< orphan*/  wf_ad7417_adc_ops ; 
 int /*<<< orphan*/  wf_ad7417_add_sensor (struct wf_ad7417_priv*,int,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wf_ad7417_init_chip (struct wf_ad7417_priv*) ; 
 int /*<<< orphan*/  wf_ad7417_temp_ops ; 
 struct mpu_data* wf_get_mpu (int) ; 

__attribute__((used)) static int wf_ad7417_probe(struct i2c_client *client,
			   const struct i2c_device_id *id)
{
	struct wf_ad7417_priv *pv;
	const struct mpu_data *mpu;
	const char *loc;
	int cpu_nr;

	loc = of_get_property(client->dev.of_node, "hwsensor-location", NULL);
	if (!loc) {
		dev_warn(&client->dev, "Missing hwsensor-location property!\n");
		return -ENXIO;
	}

	/*
	 * Identify which CPU we belong to by looking at the first entry
	 * in the hwsensor-location list
	 */
	if (!strncmp(loc, "CPU A", 5))
		cpu_nr = 0;
	else if (!strncmp(loc, "CPU B", 5))
		cpu_nr = 1;
	else {
		pr_err("wf_ad7417: Can't identify location %s\n", loc);
		return -ENXIO;
	}
	mpu = wf_get_mpu(cpu_nr);
	if (!mpu) {
		dev_err(&client->dev, "Failed to retrieve MPU data\n");
		return -ENXIO;
	}

	pv = kzalloc(sizeof(struct wf_ad7417_priv), GFP_KERNEL);
	if (pv == NULL)
		return -ENODEV;

	kref_init(&pv->ref);
	mutex_init(&pv->lock);
	pv->i2c = client;
	pv->cpu = cpu_nr;
	pv->mpu = mpu;
	dev_set_drvdata(&client->dev, pv);

	/* Initialize the chip */
	wf_ad7417_init_chip(pv);

	/*
	 * We cannot rely on Apple device-tree giving us child
	 * node with the names of the individual sensors so we
	 * just hard code what we know about them
	 */
	wf_ad7417_add_sensor(pv, 0, "cpu-amb-temp", &wf_ad7417_temp_ops);
	wf_ad7417_add_sensor(pv, 1, "cpu-diode-temp", &wf_ad7417_adc_ops);
	wf_ad7417_add_sensor(pv, 2, "cpu-12v-current", &wf_ad7417_adc_ops);
	wf_ad7417_add_sensor(pv, 3, "cpu-voltage", &wf_ad7417_adc_ops);
	wf_ad7417_add_sensor(pv, 4, "cpu-current", &wf_ad7417_adc_ops);

	return 0;
}