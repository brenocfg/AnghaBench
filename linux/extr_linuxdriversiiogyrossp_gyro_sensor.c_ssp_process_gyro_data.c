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
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  SSP_GYROSCOPE_SIZE ; 
 int ssp_common_process_data (struct iio_dev*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ssp_process_gyro_data(struct iio_dev *indio_dev, void *buf,
				 int64_t timestamp)
{
	return ssp_common_process_data(indio_dev, buf, SSP_GYROSCOPE_SIZE,
				       timestamp);
}