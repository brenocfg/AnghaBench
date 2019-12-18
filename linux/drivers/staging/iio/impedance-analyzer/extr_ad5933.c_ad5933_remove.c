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
struct iio_dev {int /*<<< orphan*/  buffer; } ;
struct i2c_client {int dummy; } ;
struct ad5933_state {int /*<<< orphan*/  mclk; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct iio_dev* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  iio_device_unregister (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_kfifo_free (int /*<<< orphan*/ ) ; 
 struct ad5933_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ad5933_remove(struct i2c_client *client)
{
	struct iio_dev *indio_dev = i2c_get_clientdata(client);
	struct ad5933_state *st = iio_priv(indio_dev);

	iio_device_unregister(indio_dev);
	iio_kfifo_free(indio_dev->buffer);
	regulator_disable(st->reg);
	clk_disable_unprepare(st->mclk);

	return 0;
}