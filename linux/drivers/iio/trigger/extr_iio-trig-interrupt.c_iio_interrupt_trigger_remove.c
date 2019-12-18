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
struct platform_device {int dummy; } ;
struct iio_trigger {int dummy; } ;
struct iio_interrupt_trigger_info {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct iio_trigger*) ; 
 int /*<<< orphan*/  iio_trigger_free (struct iio_trigger*) ; 
 struct iio_interrupt_trigger_info* iio_trigger_get_drvdata (struct iio_trigger*) ; 
 int /*<<< orphan*/  iio_trigger_unregister (struct iio_trigger*) ; 
 int /*<<< orphan*/  kfree (struct iio_interrupt_trigger_info*) ; 
 struct iio_trigger* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int iio_interrupt_trigger_remove(struct platform_device *pdev)
{
	struct iio_trigger *trig;
	struct iio_interrupt_trigger_info *trig_info;

	trig = platform_get_drvdata(pdev);
	trig_info = iio_trigger_get_drvdata(trig);
	iio_trigger_unregister(trig);
	free_irq(trig_info->irq, trig);
	kfree(trig_info);
	iio_trigger_free(trig);

	return 0;
}