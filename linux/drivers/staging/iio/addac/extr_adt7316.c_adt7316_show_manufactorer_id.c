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
typedef  int u8 ;
struct iio_dev {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int (* read ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ;int /*<<< orphan*/  client; } ;
struct adt7316_chip_info {TYPE_1__ bus; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADT7316_MANUFACTURE_ID ; 
 int /*<<< orphan*/  EIO ; 
 struct iio_dev* dev_to_iio_dev (struct device*) ; 
 struct adt7316_chip_info* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static ssize_t adt7316_show_manufactorer_id(struct device *dev,
					    struct device_attribute *attr,
					    char *buf)
{
	struct iio_dev *dev_info = dev_to_iio_dev(dev);
	struct adt7316_chip_info *chip = iio_priv(dev_info);
	u8 id;
	int ret;

	ret = chip->bus.read(chip->bus.client, ADT7316_MANUFACTURE_ID, &id);
	if (ret)
		return -EIO;

	return sprintf(buf, "%d\n", id);
}