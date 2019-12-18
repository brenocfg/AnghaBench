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
struct st_uvis25_hw {int /*<<< orphan*/  trig; int /*<<< orphan*/  regmap; } ;
struct iio_poll_func {struct iio_dev* indio_dev; } ;
struct iio_dev {int dummy; } ;
typedef  int /*<<< orphan*/  s64 ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGN (int,int) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  ST_UVIS25_REG_OUT_ADDR ; 
 int /*<<< orphan*/  iio_get_time_ns (struct iio_dev*) ; 
 struct st_uvis25_hw* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_push_to_buffers_with_timestamp (struct iio_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_trigger_notify_done (int /*<<< orphan*/ ) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static irqreturn_t st_uvis25_buffer_handler_thread(int irq, void *p)
{
	u8 buffer[ALIGN(sizeof(u8), sizeof(s64)) + sizeof(s64)];
	struct iio_poll_func *pf = p;
	struct iio_dev *iio_dev = pf->indio_dev;
	struct st_uvis25_hw *hw = iio_priv(iio_dev);
	int err;

	err = regmap_read(hw->regmap, ST_UVIS25_REG_OUT_ADDR, (int *)buffer);
	if (err < 0)
		goto out;

	iio_push_to_buffers_with_timestamp(iio_dev, buffer,
					   iio_get_time_ns(iio_dev));

out:
	iio_trigger_notify_done(hw->trig);

	return IRQ_HANDLED;
}