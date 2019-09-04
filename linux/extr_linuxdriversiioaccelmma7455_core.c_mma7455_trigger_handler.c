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
typedef  int /*<<< orphan*/  u8 ;
struct mma7455_data {int /*<<< orphan*/  regmap; } ;
struct iio_poll_func {struct iio_dev* indio_dev; } ;
struct iio_dev {int /*<<< orphan*/  trig; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  MMA7455_REG_XOUTL ; 
 int /*<<< orphan*/  iio_get_time_ns (struct iio_dev*) ; 
 struct mma7455_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_push_to_buffers_with_timestamp (struct iio_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_trigger_notify_done (int /*<<< orphan*/ ) ; 
 int mma7455_drdy (struct mma7455_data*) ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static irqreturn_t mma7455_trigger_handler(int irq, void *p)
{
	struct iio_poll_func *pf = p;
	struct iio_dev *indio_dev = pf->indio_dev;
	struct mma7455_data *mma7455 = iio_priv(indio_dev);
	u8 buf[16]; /* 3 x 16-bit channels + padding + ts */
	int ret;

	ret = mma7455_drdy(mma7455);
	if (ret)
		goto done;

	ret = regmap_bulk_read(mma7455->regmap, MMA7455_REG_XOUTL, buf,
			       sizeof(__le16) * 3);
	if (ret)
		goto done;

	iio_push_to_buffers_with_timestamp(indio_dev, buf,
					   iio_get_time_ns(indio_dev));

done:
	iio_trigger_notify_done(indio_dev->trig);

	return IRQ_HANDLED;
}