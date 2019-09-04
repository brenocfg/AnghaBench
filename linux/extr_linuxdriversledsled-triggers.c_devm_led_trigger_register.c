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
struct led_trigger {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  devm_led_trigger_release ; 
 int /*<<< orphan*/  devres_add (struct device*,struct led_trigger**) ; 
 struct led_trigger** devres_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_free (struct led_trigger**) ; 
 int led_trigger_register (struct led_trigger*) ; 

int devm_led_trigger_register(struct device *dev,
			      struct led_trigger *trig)
{
	struct led_trigger **dr;
	int rc;

	dr = devres_alloc(devm_led_trigger_release, sizeof(*dr),
			  GFP_KERNEL);
	if (!dr)
		return -ENOMEM;

	*dr = trig;

	rc = led_trigger_register(trig);
	if (rc)
		devres_free(dr);
	else
		devres_add(dev, dr);

	return rc;
}