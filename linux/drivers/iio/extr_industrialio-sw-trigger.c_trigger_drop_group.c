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
struct iio_sw_trigger {int dummy; } ;
struct config_item {int dummy; } ;
struct config_group {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  config_item_put (struct config_item*) ; 
 int /*<<< orphan*/  iio_sw_trigger_destroy (struct iio_sw_trigger*) ; 
 struct iio_sw_trigger* to_iio_sw_trigger (struct config_item*) ; 

__attribute__((used)) static void trigger_drop_group(struct config_group *group,
			       struct config_item *item)
{
	struct iio_sw_trigger *t = to_iio_sw_trigger(item);

	iio_sw_trigger_destroy(t);
	config_item_put(item);
}