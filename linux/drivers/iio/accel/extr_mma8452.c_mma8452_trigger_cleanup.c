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
struct iio_dev {scalar_t__ trig; } ;

/* Variables and functions */
 int /*<<< orphan*/  iio_trigger_unregister (scalar_t__) ; 

__attribute__((used)) static void mma8452_trigger_cleanup(struct iio_dev *indio_dev)
{
	if (indio_dev->trig)
		iio_trigger_unregister(indio_dev->trig);
}