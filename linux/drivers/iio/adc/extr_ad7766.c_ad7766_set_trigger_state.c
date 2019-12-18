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
struct iio_trigger {int dummy; } ;
struct ad7766 {TYPE_1__* spi; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 struct ad7766* iio_trigger_get_drvdata (struct iio_trigger*) ; 

__attribute__((used)) static int ad7766_set_trigger_state(struct iio_trigger *trig, bool enable)
{
	struct ad7766 *ad7766 = iio_trigger_get_drvdata(trig);

	if (enable)
		enable_irq(ad7766->spi->irq);
	else
		disable_irq(ad7766->spi->irq);

	return 0;
}