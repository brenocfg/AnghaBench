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
struct ad7266_state {int dummy; } ;

/* Variables and functions */
 int ad7266_powerdown (struct ad7266_state*) ; 
 struct ad7266_state* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int ad7266_postdisable(struct iio_dev *indio_dev)
{
	struct ad7266_state *st = iio_priv(indio_dev);
	return ad7266_powerdown(st);
}