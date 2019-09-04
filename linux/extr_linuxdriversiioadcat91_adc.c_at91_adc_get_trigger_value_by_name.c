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
struct iio_dev {int /*<<< orphan*/  id; int /*<<< orphan*/  name; } ;
struct at91_adc_trigger {scalar_t__ value; int /*<<< orphan*/  name; } ;
struct at91_adc_state {int trigger_number; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct at91_adc_state* iio_priv (struct iio_dev*) ; 
 char* kasprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int at91_adc_get_trigger_value_by_name(struct iio_dev *idev,
					     struct at91_adc_trigger *triggers,
					     const char *trigger_name)
{
	struct at91_adc_state *st = iio_priv(idev);
	int i;

	for (i = 0; i < st->trigger_number; i++) {
		char *name = kasprintf(GFP_KERNEL,
				"%s-dev%d-%s",
				idev->name,
				idev->id,
				triggers[i].name);
		if (!name)
			return -ENOMEM;

		if (strcmp(trigger_name, name) == 0) {
			kfree(name);
			if (triggers[i].value == 0)
				return -EINVAL;
			return triggers[i].value;
		}

		kfree(name);
	}

	return -EINVAL;
}