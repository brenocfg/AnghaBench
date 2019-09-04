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
struct iio_dev {int* active_scan_mask; } ;
struct ad7887_state {int /*<<< orphan*/ * msg; int /*<<< orphan*/ * ring_msg; int /*<<< orphan*/  spi; } ;

/* Variables and functions */
 size_t AD7887_CH0 ; 
 size_t AD7887_CH0_CH1 ; 
 size_t AD7887_CH1 ; 
 struct ad7887_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  spi_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ad7887_ring_preenable(struct iio_dev *indio_dev)
{
	struct ad7887_state *st = iio_priv(indio_dev);

	/* We know this is a single long so can 'cheat' */
	switch (*indio_dev->active_scan_mask) {
	case (1 << 0):
		st->ring_msg = &st->msg[AD7887_CH0];
		break;
	case (1 << 1):
		st->ring_msg = &st->msg[AD7887_CH1];
		/* Dummy read: push CH1 setting down to hardware */
		spi_sync(st->spi, st->ring_msg);
		break;
	case ((1 << 1) | (1 << 0)):
		st->ring_msg = &st->msg[AD7887_CH0_CH1];
		break;
	}

	return 0;
}