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
struct iio_dev {int dummy; } ;
struct TYPE_2__ {int len; } ;
struct adc084s021 {int /*<<< orphan*/  reg; TYPE_1__ spi_trans; } ;

/* Variables and functions */
 struct adc084s021* iio_priv (struct iio_dev*) ; 
 int regulator_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adc084s021_buffer_postdisable(struct iio_dev *indio_dev)
{
	struct adc084s021 *adc = iio_priv(indio_dev);

	adc->spi_trans.len = 4; /* Trash + single channel */

	return regulator_disable(adc->reg);
}