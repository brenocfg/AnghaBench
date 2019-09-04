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
struct genwqe_dev {int softreset; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 int /*<<< orphan*/  IO_SLC_CFGREG_SOFTRESET ; 
 int /*<<< orphan*/  __genwqe_writeq (struct genwqe_dev*,int /*<<< orphan*/ ,int) ; 
 struct genwqe_dev* dev_get_drvdata (struct device*) ; 
 scalar_t__ kstrtoint (char const*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static ssize_t next_bitstream_store(struct device *dev,
				    struct device_attribute *attr,
				    const char *buf, size_t count)
{
	int partition;
	struct genwqe_dev *cd = dev_get_drvdata(dev);

	if (kstrtoint(buf, 0, &partition) < 0)
		return -EINVAL;

	switch (partition) {
	case 0x0:
		cd->softreset = 0x78;
		break;
	case 0x1:
		cd->softreset = 0x7c;
		break;
	default:
		return -EINVAL;
	}

	__genwqe_writeq(cd, IO_SLC_CFGREG_SOFTRESET, cd->softreset);
	return count;
}