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
typedef  int u16 ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_4__ {int* reg; int /*<<< orphan*/  update_lock; } ;
struct TYPE_3__ {size_t* msb; size_t* lsb; } ;

/* Variables and functions */
 int /*<<< orphan*/  SETUP_SHOW_DATA_PARAM (struct device*,struct device_attribute*) ; 
 TYPE_2__* data ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* param ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t show_fan16(struct device *dev,
			  struct device_attribute *attr, char *buf)
{
	SETUP_SHOW_DATA_PARAM(dev, attr);
	u16 regval;

	mutex_lock(&data->update_lock);
	regval = (data->reg[param->msb[0]] << 8) | data->reg[param->lsb[0]];
	mutex_unlock(&data->update_lock);

	return sprintf(buf, "%u\n",
		       (regval == 0 ? -1 : (regval) ==
			0xffff ? 0 : 5400000 / regval));
}