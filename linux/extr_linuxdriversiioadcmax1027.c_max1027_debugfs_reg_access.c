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
typedef  scalar_t__ u8 ;
struct max1027_state {int /*<<< orphan*/  spi; scalar_t__ buffer; } ;
struct iio_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct max1027_state* iio_priv (struct iio_dev*) ; 
 int spi_write (int /*<<< orphan*/ ,scalar_t__*,int) ; 

__attribute__((used)) static int max1027_debugfs_reg_access(struct iio_dev *indio_dev,
				      unsigned reg, unsigned writeval,
				      unsigned *readval)
{
	struct max1027_state *st = iio_priv(indio_dev);
	u8 *val = (u8 *)st->buffer;

	if (readval != NULL)
		return -EINVAL;

	*val = (u8)writeval;
	return spi_write(st->spi, val, 1);
}