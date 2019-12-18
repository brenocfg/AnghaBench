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
struct iio_dev {int dummy; } ;
struct adxl372_state {int /*<<< orphan*/  fifo_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADXL372_FIFO_BYPASSED ; 
 int /*<<< orphan*/  adxl372_configure_fifo (struct adxl372_state*) ; 
 int /*<<< orphan*/  adxl372_set_interrupts (struct adxl372_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct adxl372_state* iio_priv (struct iio_dev*) ; 
 int iio_triggered_buffer_predisable (struct iio_dev*) ; 

__attribute__((used)) static int adxl372_buffer_predisable(struct iio_dev *indio_dev)
{
	struct adxl372_state *st = iio_priv(indio_dev);

	adxl372_set_interrupts(st, 0, 0);
	st->fifo_mode = ADXL372_FIFO_BYPASSED;
	adxl372_configure_fifo(st);

	return iio_triggered_buffer_predisable(indio_dev);
}