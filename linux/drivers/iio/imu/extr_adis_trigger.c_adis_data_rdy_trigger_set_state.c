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
struct iio_trigger {int dummy; } ;
struct adis {int dummy; } ;

/* Variables and functions */
 int adis_enable_irq (struct adis*,int) ; 
 struct adis* iio_trigger_get_drvdata (struct iio_trigger*) ; 

__attribute__((used)) static int adis_data_rdy_trigger_set_state(struct iio_trigger *trig,
						bool state)
{
	struct adis *adis = iio_trigger_get_drvdata(trig);

	return adis_enable_irq(adis, state);
}