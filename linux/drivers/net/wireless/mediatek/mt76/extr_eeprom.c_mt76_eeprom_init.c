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
struct TYPE_2__ {int size; int /*<<< orphan*/  data; } ;
struct mt76_dev {TYPE_1__ eeprom; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_get_of_eeprom (struct mt76_dev*,int) ; 

int
mt76_eeprom_init(struct mt76_dev *dev, int len)
{
	dev->eeprom.size = len;
	dev->eeprom.data = devm_kzalloc(dev->dev, len, GFP_KERNEL);
	if (!dev->eeprom.data)
		return -ENOMEM;

	return !mt76_get_of_eeprom(dev, len);
}