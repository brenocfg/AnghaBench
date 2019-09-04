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
struct spi_device {int bits_per_word; int /*<<< orphan*/  dev; } ;
struct max7301 {int /*<<< orphan*/ * dev; int /*<<< orphan*/  write; int /*<<< orphan*/  read; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int __max730x_probe (struct max7301*) ; 
 struct max7301* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max7301_spi_read ; 
 int /*<<< orphan*/  max7301_spi_write ; 
 int spi_setup (struct spi_device*) ; 

__attribute__((used)) static int max7301_probe(struct spi_device *spi)
{
	struct max7301 *ts;
	int ret;

	/* bits_per_word cannot be configured in platform data */
	spi->bits_per_word = 16;
	ret = spi_setup(spi);
	if (ret < 0)
		return ret;

	ts = devm_kzalloc(&spi->dev, sizeof(struct max7301), GFP_KERNEL);
	if (!ts)
		return -ENOMEM;

	ts->read = max7301_spi_read;
	ts->write = max7301_spi_write;
	ts->dev = &spi->dev;

	ret = __max730x_probe(ts);
	return ret;
}