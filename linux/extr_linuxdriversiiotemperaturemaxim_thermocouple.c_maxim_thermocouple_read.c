#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct maxim_thermocouple_data {TYPE_1__* chip; int /*<<< orphan*/  spi; } ;
struct TYPE_4__ {int shift; scalar_t__ realbits; } ;
struct iio_chan_spec {int address; TYPE_2__ scan_type; } ;
typedef  int /*<<< orphan*/  __be32 ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_3__ {unsigned int read_size; int status_bit; } ;

/* Variables and functions */
 int EINVAL ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int sign_extend32 (int,scalar_t__) ; 
 int spi_read (int /*<<< orphan*/ ,void*,unsigned int) ; 

__attribute__((used)) static int maxim_thermocouple_read(struct maxim_thermocouple_data *data,
				   struct iio_chan_spec const *chan, int *val)
{
	unsigned int storage_bytes = data->chip->read_size;
	unsigned int shift = chan->scan_type.shift + (chan->address * 8);
	__be16 buf16;
	__be32 buf32;
	int ret;

	switch (storage_bytes) {
	case 2:
		ret = spi_read(data->spi, (void *)&buf16, storage_bytes);
		*val = be16_to_cpu(buf16);
		break;
	case 4:
		ret = spi_read(data->spi, (void *)&buf32, storage_bytes);
		*val = be32_to_cpu(buf32);
		break;
	default:
		ret = -EINVAL;
	}

	if (ret)
		return ret;

	/* check to be sure this is a valid reading */
	if (*val & data->chip->status_bit)
		return -EINVAL;

	*val = sign_extend32(*val >> shift, chan->scan_type.realbits - 1);

	return 0;
}