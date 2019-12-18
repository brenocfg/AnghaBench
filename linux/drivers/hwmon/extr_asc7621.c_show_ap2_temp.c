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
typedef  int u8 ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int s8 ;
struct TYPE_4__ {int* reg; int /*<<< orphan*/  update_lock; } ;
struct TYPE_3__ {size_t* msb; int* shift; int* mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  SETUP_SHOW_DATA_PARAM (struct device*,struct device_attribute*) ; 
 long* asc7621_range_map ; 
 size_t clamp_val (int,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* data ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* param ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t show_ap2_temp(struct device *dev,
			     struct device_attribute *attr, char *buf)
{
	SETUP_SHOW_DATA_PARAM(dev, attr);
	long auto_point1;
	u8 regval;
	int temp;

	mutex_lock(&data->update_lock);
	auto_point1 = ((s8) data->reg[param->msb[1]]) * 1000;
	regval =
	    ((data->reg[param->msb[0]] >> param->shift[0]) & param->mask[0]);
	temp = auto_point1 + asc7621_range_map[clamp_val(regval, 0, 15)];
	mutex_unlock(&data->update_lock);

	return sprintf(buf, "%d\n", temp);

}