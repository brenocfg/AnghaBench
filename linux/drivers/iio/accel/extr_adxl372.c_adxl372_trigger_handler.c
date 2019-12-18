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
typedef  int u16 ;
struct iio_poll_func {struct iio_dev* indio_dev; } ;
struct iio_dev {int /*<<< orphan*/  trig; } ;
struct adxl372_state {scalar_t__ fifo_mode; int /*<<< orphan*/ * fifo_buf; scalar_t__ fifo_set_size; int /*<<< orphan*/  regmap; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ ADXL372_FIFO_BYPASSED ; 
 int /*<<< orphan*/  ADXL372_FIFO_DATA ; 
 scalar_t__ ADXL372_STATUS_1_FIFO_FULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int adxl372_get_status (struct adxl372_state*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 struct adxl372_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_push_to_buffers (struct iio_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iio_trigger_notify_done (int /*<<< orphan*/ ) ; 
 int regmap_noinc_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static irqreturn_t adxl372_trigger_handler(int irq, void  *p)
{
	struct iio_poll_func *pf = p;
	struct iio_dev *indio_dev = pf->indio_dev;
	struct adxl372_state *st = iio_priv(indio_dev);
	u8 status1, status2;
	u16 fifo_entries;
	int i, ret;

	ret = adxl372_get_status(st, &status1, &status2, &fifo_entries);
	if (ret < 0)
		goto err;

	if (st->fifo_mode != ADXL372_FIFO_BYPASSED &&
	    ADXL372_STATUS_1_FIFO_FULL(status1)) {
		/*
		 * When reading data from multiple axes from the FIFO,
		 * to ensure that data is not overwritten and stored out
		 * of order at least one sample set must be left in the
		 * FIFO after every read.
		 */
		fifo_entries -= st->fifo_set_size;

		/* Read data from the FIFO */
		ret = regmap_noinc_read(st->regmap, ADXL372_FIFO_DATA,
					st->fifo_buf,
					fifo_entries * sizeof(u16));
		if (ret < 0)
			goto err;

		/* Each sample is 2 bytes */
		for (i = 0; i < fifo_entries; i += st->fifo_set_size)
			iio_push_to_buffers(indio_dev, &st->fifo_buf[i]);
	}
err:
	iio_trigger_notify_done(indio_dev->trig);
	return IRQ_HANDLED;
}