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
struct xadc {int /*<<< orphan*/  data; int /*<<< orphan*/  clk; int /*<<< orphan*/  zynq_unmask_work; int /*<<< orphan*/  irq; int /*<<< orphan*/  convst_trigger; int /*<<< orphan*/  samplerate_trigger; TYPE_1__* ops; } ;
struct platform_device {int dummy; } ;
struct iio_dev {int /*<<< orphan*/  channels; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int XADC_FLAGS_BUFFERED ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct iio_dev*) ; 
 int /*<<< orphan*/  iio_device_unregister (struct iio_dev*) ; 
 struct xadc* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_trigger_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_triggered_buffer_cleanup (struct iio_dev*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 struct iio_dev* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int xadc_remove(struct platform_device *pdev)
{
	struct iio_dev *indio_dev = platform_get_drvdata(pdev);
	struct xadc *xadc = iio_priv(indio_dev);

	iio_device_unregister(indio_dev);
	if (xadc->ops->flags & XADC_FLAGS_BUFFERED) {
		iio_trigger_free(xadc->samplerate_trigger);
		iio_trigger_free(xadc->convst_trigger);
		iio_triggered_buffer_cleanup(indio_dev);
	}
	free_irq(xadc->irq, indio_dev);
	cancel_delayed_work_sync(&xadc->zynq_unmask_work);
	clk_disable_unprepare(xadc->clk);
	kfree(xadc->data);
	kfree(indio_dev->channels);

	return 0;
}