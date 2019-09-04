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
struct bmc150_accel_data {TYPE_1__* triggers; } ;
struct TYPE_2__ {int /*<<< orphan*/ * indio_trig; } ;

/* Variables and functions */
 int /*<<< orphan*/  iio_trigger_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bmc150_accel_unregister_triggers(struct bmc150_accel_data *data,
					     int from)
{
	int i;

	for (i = from; i >= 0; i--) {
		if (data->triggers[i].indio_trig) {
			iio_trigger_unregister(data->triggers[i].indio_trig);
			data->triggers[i].indio_trig = NULL;
		}
	}
}