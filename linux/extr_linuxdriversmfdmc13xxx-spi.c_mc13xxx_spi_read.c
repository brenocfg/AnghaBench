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
struct spi_transfer {unsigned char* tx_buf; unsigned char* rx_buf; int len; } ;
struct spi_message {int dummy; } ;
struct spi_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  spi_message_add_tail (struct spi_transfer*,struct spi_message*) ; 
 int /*<<< orphan*/  spi_message_init (struct spi_message*) ; 
 int spi_sync (struct spi_device*,struct spi_message*) ; 
 struct spi_device* to_spi_device (struct device*) ; 

__attribute__((used)) static int mc13xxx_spi_read(void *context, const void *reg, size_t reg_size,
				void *val, size_t val_size)
{
	unsigned char w[4] = { *((unsigned char *) reg), 0, 0, 0};
	unsigned char r[4];
	unsigned char *p = val;
	struct device *dev = context;
	struct spi_device *spi = to_spi_device(dev);
	struct spi_transfer t = {
		.tx_buf = w,
		.rx_buf = r,
		.len = 4,
	};

	struct spi_message m;
	int ret;

	if (val_size != 3 || reg_size != 1)
		return -ENOTSUPP;

	spi_message_init(&m);
	spi_message_add_tail(&t, &m);
	ret = spi_sync(spi, &m);

	memcpy(p, &r[1], 3);

	return ret;
}