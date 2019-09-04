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
typedef  int /*<<< orphan*/  u32 ;
struct iio_poll_func {struct iio_dev* indio_dev; } ;
struct iio_dev {int /*<<< orphan*/  trig; } ;
struct hi8435_priv {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  HI8435_SO31_0_REG ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  hi8435_iio_push_event (struct iio_dev*,int /*<<< orphan*/ ) ; 
 int hi8435_readl (struct hi8435_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct hi8435_priv* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_trigger_notify_done (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t hi8435_trigger_handler(int irq, void *private)
{
	struct iio_poll_func *pf = private;
	struct iio_dev *idev = pf->indio_dev;
	struct hi8435_priv *priv = iio_priv(idev);
	u32 val;
	int ret;

	ret = hi8435_readl(priv, HI8435_SO31_0_REG, &val);
	if (ret < 0)
		goto err_read;

	hi8435_iio_push_event(idev, val);

err_read:
	iio_trigger_notify_done(idev->trig);

	return IRQ_HANDLED;
}