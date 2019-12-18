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
typedef  int u8 ;
struct iio_dev {int dummy; } ;
struct TYPE_2__ {int (* read ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ;int /*<<< orphan*/  client; } ;
struct adt7316_chip_info {int id; TYPE_1__ bus; } ;
typedef  int /*<<< orphan*/  s64 ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int ADT7316_INT_MASK2_VDD ; 
 int /*<<< orphan*/  ADT7316_INT_STAT1 ; 
 int /*<<< orphan*/  ADT7316_INT_STAT2 ; 
 int BIT (int) ; 
 int ID_ADT75XX ; 
 int ID_FAMILY_MASK ; 
 int /*<<< orphan*/  IIO_EV_DIR_EITHER ; 
 int /*<<< orphan*/  IIO_EV_DIR_FALLING ; 
 int /*<<< orphan*/  IIO_EV_DIR_RISING ; 
 int /*<<< orphan*/  IIO_EV_TYPE_THRESH ; 
 int /*<<< orphan*/  IIO_TEMP ; 
 int /*<<< orphan*/  IIO_UNMOD_EVENT_CODE (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IIO_VOLTAGE ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  iio_get_time_ns (struct iio_dev*) ; 
 struct adt7316_chip_info* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_push_event (struct iio_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static irqreturn_t adt7316_event_handler(int irq, void *private)
{
	struct iio_dev *indio_dev = private;
	struct adt7316_chip_info *chip = iio_priv(indio_dev);
	u8 stat1, stat2;
	int ret;
	s64 time;

	ret = chip->bus.read(chip->bus.client, ADT7316_INT_STAT1, &stat1);
	if (!ret) {
		if ((chip->id & ID_FAMILY_MASK) != ID_ADT75XX)
			stat1 &= 0x1F;

		time = iio_get_time_ns(indio_dev);
		if (stat1 & BIT(0))
			iio_push_event(indio_dev,
				       IIO_UNMOD_EVENT_CODE(IIO_TEMP, 0,
							    IIO_EV_TYPE_THRESH,
							    IIO_EV_DIR_RISING),
				       time);
		if (stat1 & BIT(1))
			iio_push_event(indio_dev,
				       IIO_UNMOD_EVENT_CODE(IIO_TEMP, 0,
							    IIO_EV_TYPE_THRESH,
							    IIO_EV_DIR_FALLING),
				       time);
		if (stat1 & BIT(2))
			iio_push_event(indio_dev,
				       IIO_UNMOD_EVENT_CODE(IIO_TEMP, 1,
							    IIO_EV_TYPE_THRESH,
							    IIO_EV_DIR_RISING),
				       time);
		if (stat1 & BIT(3))
			iio_push_event(indio_dev,
				       IIO_UNMOD_EVENT_CODE(IIO_TEMP, 1,
							    IIO_EV_TYPE_THRESH,
							    IIO_EV_DIR_FALLING),
				       time);
		if (stat1 & BIT(5))
			iio_push_event(indio_dev,
				       IIO_UNMOD_EVENT_CODE(IIO_VOLTAGE, 1,
							    IIO_EV_TYPE_THRESH,
							    IIO_EV_DIR_EITHER),
				       time);
		if (stat1 & BIT(6))
			iio_push_event(indio_dev,
				       IIO_UNMOD_EVENT_CODE(IIO_VOLTAGE, 2,
							    IIO_EV_TYPE_THRESH,
							    IIO_EV_DIR_EITHER),
				       time);
		if (stat1 & BIT(7))
			iio_push_event(indio_dev,
				       IIO_UNMOD_EVENT_CODE(IIO_VOLTAGE, 3,
							    IIO_EV_TYPE_THRESH,
							    IIO_EV_DIR_EITHER),
				       time);
		}
	ret = chip->bus.read(chip->bus.client, ADT7316_INT_STAT2, &stat2);
	if (!ret) {
		if (stat2 & ADT7316_INT_MASK2_VDD)
			iio_push_event(indio_dev,
				       IIO_UNMOD_EVENT_CODE(IIO_VOLTAGE,
							    0,
							    IIO_EV_TYPE_THRESH,
							    IIO_EV_DIR_RISING),
				       iio_get_time_ns(indio_dev));
	}

	return IRQ_HANDLED;
}