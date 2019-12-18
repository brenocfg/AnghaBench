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
struct as3935_state {int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 struct as3935_state* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static void as3935_stop_work(void *data)
{
	struct iio_dev *indio_dev = data;
	struct as3935_state *st = iio_priv(indio_dev);

	cancel_delayed_work_sync(&st->work);
}