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
struct spi_transfer {void const* tx_buf; size_t len; } ;
struct spi_message {int dummy; } ;
struct spi_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  spi_message_add_tail (struct spi_transfer*,struct spi_message*) ; 
 int /*<<< orphan*/  spi_message_init (struct spi_message*) ; 
 int spi_sync (struct spi_device*,struct spi_message*) ; 
 struct spi_device* to_spi_device (struct device*) ; 

__attribute__((used)) static int regmap_spi_gather_write(void *context,
				   const void *reg, size_t reg_len,
				   const void *val, size_t val_len)
{
	struct device *dev = context;
	struct spi_device *spi = to_spi_device(dev);
	struct spi_message m;
	struct spi_transfer t[2] = { { .tx_buf = reg, .len = reg_len, },
				     { .tx_buf = val, .len = val_len, }, };

	spi_message_init(&m);
	spi_message_add_tail(&t[0], &m);
	spi_message_add_tail(&t[1], &m);

	return spi_sync(spi, &m);
}