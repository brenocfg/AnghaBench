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
struct iio_dev {scalar_t__ currentmode; } ;

/* Variables and functions */
 scalar_t__ INDIO_BUFFER_TRIGGERED ; 
 int /*<<< orphan*/  __stm32_dfsdm_predisable (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_triggered_buffer_predisable (struct iio_dev*) ; 

__attribute__((used)) static int stm32_dfsdm_predisable(struct iio_dev *indio_dev)
{
	__stm32_dfsdm_predisable(indio_dev);

	if (indio_dev->currentmode == INDIO_BUFFER_TRIGGERED)
		iio_triggered_buffer_predisable(indio_dev);

	return 0;
}