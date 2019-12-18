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
struct gpio_keys_drvdata {int /*<<< orphan*/  disable_lock; struct gpio_button_data* data; TYPE_1__* pdata; int /*<<< orphan*/  input; } ;
struct gpio_button_data {int /*<<< orphan*/ * code; TYPE_2__* button; } ;
typedef  int ssize_t ;
struct TYPE_4__ {unsigned int type; int /*<<< orphan*/  can_disable; } ;
struct TYPE_3__ {int nbuttons; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  bitmap_free (unsigned long*) ; 
 int bitmap_parselist (char const*,unsigned long*,int) ; 
 int /*<<< orphan*/  bitmap_subset (unsigned long*,unsigned long const*,int) ; 
 unsigned long* bitmap_zalloc (int,int /*<<< orphan*/ ) ; 
 unsigned long* get_bm_events_by_type (int /*<<< orphan*/ ,unsigned int) ; 
 int get_n_events_by_type (unsigned int) ; 
 int /*<<< orphan*/  gpio_keys_disable_button (struct gpio_button_data*) ; 
 int /*<<< orphan*/  gpio_keys_enable_button (struct gpio_button_data*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static ssize_t gpio_keys_attr_store_helper(struct gpio_keys_drvdata *ddata,
					   const char *buf, unsigned int type)
{
	int n_events = get_n_events_by_type(type);
	const unsigned long *bitmap = get_bm_events_by_type(ddata->input, type);
	unsigned long *bits;
	ssize_t error;
	int i;

	bits = bitmap_zalloc(n_events, GFP_KERNEL);
	if (!bits)
		return -ENOMEM;

	error = bitmap_parselist(buf, bits, n_events);
	if (error)
		goto out;

	/* First validate */
	if (!bitmap_subset(bits, bitmap, n_events)) {
		error = -EINVAL;
		goto out;
	}

	for (i = 0; i < ddata->pdata->nbuttons; i++) {
		struct gpio_button_data *bdata = &ddata->data[i];

		if (bdata->button->type != type)
			continue;

		if (test_bit(*bdata->code, bits) &&
		    !bdata->button->can_disable) {
			error = -EINVAL;
			goto out;
		}
	}

	mutex_lock(&ddata->disable_lock);

	for (i = 0; i < ddata->pdata->nbuttons; i++) {
		struct gpio_button_data *bdata = &ddata->data[i];

		if (bdata->button->type != type)
			continue;

		if (test_bit(*bdata->code, bits))
			gpio_keys_disable_button(bdata);
		else
			gpio_keys_enable_button(bdata);
	}

	mutex_unlock(&ddata->disable_lock);

out:
	bitmap_free(bits);
	return error;
}