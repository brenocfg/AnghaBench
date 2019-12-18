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
struct TYPE_3__ {int mode; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {TYPE_1__ attr; int /*<<< orphan*/  store; int /*<<< orphan*/  show; } ;
struct iio_dev_attr {int address; TYPE_2__ dev_attr; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ad7280_show_balance_sw ; 
 int /*<<< orphan*/  ad7280_store_balance_sw ; 
 int /*<<< orphan*/  devm_kasprintf (struct device*,int /*<<< orphan*/ ,char*,int,int) ; 

__attribute__((used)) static int ad7280_balance_switch_attr_init(struct iio_dev_attr *attr,
					   struct device *dev, int addr, int i)
{
	attr->address = addr;
	attr->dev_attr.attr.mode = 0644;
	attr->dev_attr.show = ad7280_show_balance_sw;
	attr->dev_attr.store = ad7280_store_balance_sw;
	attr->dev_attr.attr.name = devm_kasprintf(dev, GFP_KERNEL,
						  "in%d-in%d_balance_switch_en",
						  i, i + 1);
	if (!attr->dev_attr.attr.name)
		return -ENOMEM;

	return 0;
}