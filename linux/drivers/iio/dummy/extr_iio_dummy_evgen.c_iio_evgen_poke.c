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
struct iio_dev_attr {size_t address; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_4__ {int /*<<< orphan*/  irq_sim; TYPE_1__* regs; } ;
struct TYPE_3__ {size_t reg_id; unsigned long reg_data; } ;

/* Variables and functions */
 TYPE_2__* iio_evgen ; 
 int /*<<< orphan*/  irq_sim_fire (int /*<<< orphan*/ *,size_t) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 
 struct iio_dev_attr* to_iio_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t iio_evgen_poke(struct device *dev,
			      struct device_attribute *attr,
			      const char *buf,
			      size_t len)
{
	struct iio_dev_attr *this_attr = to_iio_dev_attr(attr);
	unsigned long event;
	int ret;

	ret = kstrtoul(buf, 10, &event);
	if (ret)
		return ret;

	iio_evgen->regs[this_attr->address].reg_id   = this_attr->address;
	iio_evgen->regs[this_attr->address].reg_data = event;

	irq_sim_fire(&iio_evgen->irq_sim, this_attr->address);

	return len;
}