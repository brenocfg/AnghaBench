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
typedef  size_t u8 ;
struct iio_dev_attr {TYPE_2__* c; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_3__ {size_t endianness; int repeat; int sign; int realbits; int storagebits; int /*<<< orphan*/  shift; } ;
struct TYPE_4__ {TYPE_1__ scan_type; } ;

/* Variables and functions */
 size_t IIO_BE ; 
 size_t IIO_CPU ; 
 size_t IIO_LE ; 
 char** iio_endian_prefix ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,int,int,int,int,...) ; 
 struct iio_dev_attr* to_iio_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t iio_show_fixed_type(struct device *dev,
				   struct device_attribute *attr,
				   char *buf)
{
	struct iio_dev_attr *this_attr = to_iio_dev_attr(attr);
	u8 type = this_attr->c->scan_type.endianness;

	if (type == IIO_CPU) {
#ifdef __LITTLE_ENDIAN
		type = IIO_LE;
#else
		type = IIO_BE;
#endif
	}
	if (this_attr->c->scan_type.repeat > 1)
		return sprintf(buf, "%s:%c%d/%dX%d>>%u\n",
		       iio_endian_prefix[type],
		       this_attr->c->scan_type.sign,
		       this_attr->c->scan_type.realbits,
		       this_attr->c->scan_type.storagebits,
		       this_attr->c->scan_type.repeat,
		       this_attr->c->scan_type.shift);
		else
			return sprintf(buf, "%s:%c%d/%d>>%u\n",
		       iio_endian_prefix[type],
		       this_attr->c->scan_type.sign,
		       this_attr->c->scan_type.realbits,
		       this_attr->c->scan_type.storagebits,
		       this_attr->c->scan_type.shift);
}