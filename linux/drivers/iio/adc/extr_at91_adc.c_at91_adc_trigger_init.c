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
struct iio_dev {int /*<<< orphan*/  dev; } ;
struct at91_adc_state {int trigger_number; int /*<<< orphan*/ ** trig; TYPE_1__* trigger_list; int /*<<< orphan*/  use_external; } ;
struct TYPE_2__ {scalar_t__ is_external; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/ * at91_adc_allocate_trigger (struct iio_dev*,TYPE_1__*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/ ** devm_kcalloc (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 struct at91_adc_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_trigger_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iio_trigger_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int at91_adc_trigger_init(struct iio_dev *idev)
{
	struct at91_adc_state *st = iio_priv(idev);
	int i, ret;

	st->trig = devm_kcalloc(&idev->dev,
				st->trigger_number, sizeof(*st->trig),
				GFP_KERNEL);

	if (st->trig == NULL) {
		ret = -ENOMEM;
		goto error_ret;
	}

	for (i = 0; i < st->trigger_number; i++) {
		if (st->trigger_list[i].is_external && !(st->use_external))
			continue;

		st->trig[i] = at91_adc_allocate_trigger(idev,
							st->trigger_list + i);
		if (st->trig[i] == NULL) {
			dev_err(&idev->dev,
				"Could not allocate trigger %d\n", i);
			ret = -ENOMEM;
			goto error_trigger;
		}
	}

	return 0;

error_trigger:
	for (i--; i >= 0; i--) {
		iio_trigger_unregister(st->trig[i]);
		iio_trigger_free(st->trig[i]);
	}
error_ret:
	return ret;
}