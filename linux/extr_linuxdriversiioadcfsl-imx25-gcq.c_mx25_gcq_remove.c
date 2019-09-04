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
struct mx25_gcq_priv {scalar_t__* vref; int /*<<< orphan*/  clk; int /*<<< orphan*/  irq; } ;
struct iio_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct mx25_gcq_priv*) ; 
 int /*<<< orphan*/  iio_device_unregister (struct iio_dev*) ; 
 struct mx25_gcq_priv* iio_priv (struct iio_dev*) ; 
 struct iio_dev* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  regulator_disable (scalar_t__) ; 

__attribute__((used)) static int mx25_gcq_remove(struct platform_device *pdev)
{
	struct iio_dev *indio_dev = platform_get_drvdata(pdev);
	struct mx25_gcq_priv *priv = iio_priv(indio_dev);
	int i;

	iio_device_unregister(indio_dev);
	free_irq(priv->irq, priv);
	clk_disable_unprepare(priv->clk);
	for (i = 4; i-- > 0;) {
		if (priv->vref[i])
			regulator_disable(priv->vref[i]);
	}

	return 0;
}