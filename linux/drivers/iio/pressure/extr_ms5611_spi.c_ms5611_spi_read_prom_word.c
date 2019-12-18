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
typedef  int u16 ;
struct ms5611_state {int /*<<< orphan*/  client; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ MS5611_READ_PROM_WORD ; 
 int /*<<< orphan*/  dev_to_iio_dev (struct device*) ; 
 struct ms5611_state* iio_priv (int /*<<< orphan*/ ) ; 
 int spi_w8r16be (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int ms5611_spi_read_prom_word(struct device *dev, int index, u16 *word)
{
	int ret;
	struct ms5611_state *st = iio_priv(dev_to_iio_dev(dev));

	ret = spi_w8r16be(st->client, MS5611_READ_PROM_WORD + (index << 1));
	if (ret < 0)
		return ret;

	*word = ret;

	return 0;
}