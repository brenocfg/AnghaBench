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
typedef  int /*<<< orphan*/  u8 ;
struct ms5611_state {int /*<<< orphan*/  client; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MS5611_RESET ; 
 int /*<<< orphan*/  dev_to_iio_dev (struct device*) ; 
 struct ms5611_state* iio_priv (int /*<<< orphan*/ ) ; 
 int spi_write_then_read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ms5611_spi_reset(struct device *dev)
{
	u8 cmd = MS5611_RESET;
	struct ms5611_state *st = iio_priv(dev_to_iio_dev(dev));

	return spi_write_then_read(st->client, &cmd, 1, NULL, 0);
}