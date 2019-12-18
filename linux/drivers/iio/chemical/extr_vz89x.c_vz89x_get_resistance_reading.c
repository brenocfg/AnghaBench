#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct vz89x_data {int /*<<< orphan*/ * buffer; } ;
struct TYPE_2__ {int endianness; } ;
struct iio_chan_spec {size_t address; TYPE_1__ scan_type; } ;
typedef  int /*<<< orphan*/  __le32 ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EINVAL ; 
 int GENMASK (int,int /*<<< orphan*/ ) ; 
#define  IIO_BE 129 
#define  IIO_LE 128 
 int be32_to_cpup (int /*<<< orphan*/ *) ; 
 int le32_to_cpup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vz89x_get_resistance_reading(struct vz89x_data *data,
					struct iio_chan_spec const *chan,
					int *val)
{
	u8 *tmp = (u8 *) &data->buffer[chan->address];

	switch (chan->scan_type.endianness) {
	case IIO_LE:
		*val = le32_to_cpup((__le32 *) tmp) & GENMASK(23, 0);
		break;
	case IIO_BE:
		*val = be32_to_cpup((__be32 *) tmp) >> 8;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}