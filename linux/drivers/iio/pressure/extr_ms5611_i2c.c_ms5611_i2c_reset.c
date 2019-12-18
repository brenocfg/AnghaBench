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
struct ms5611_state {int /*<<< orphan*/  client; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MS5611_RESET ; 
 int /*<<< orphan*/  dev_to_iio_dev (struct device*) ; 
 int i2c_smbus_write_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ms5611_state* iio_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ms5611_i2c_reset(struct device *dev)
{
	struct ms5611_state *st = iio_priv(dev_to_iio_dev(dev));

	return i2c_smbus_write_byte(st->client, MS5611_RESET);
}