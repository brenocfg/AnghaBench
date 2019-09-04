#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  int u16 ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_6__ {int* reg; int /*<<< orphan*/  update_lock; } ;
struct TYPE_5__ {size_t* msb; size_t* lsb; } ;
struct TYPE_4__ {size_t index; } ;

/* Variables and functions */
 int /*<<< orphan*/  SETUP_SHOW_DATA_PARAM (struct device*,struct device_attribute*) ; 
 int* asc7621_in_scaling ; 
 TYPE_3__* data ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_2__* param ; 
 TYPE_1__* sda ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t show_in10(struct device *dev, struct device_attribute *attr,
			 char *buf)
{
	SETUP_SHOW_DATA_PARAM(dev, attr);
	u16 regval;
	u8 nr = sda->index;

	mutex_lock(&data->update_lock);
	regval = (data->reg[param->msb[0]] << 8) | (data->reg[param->lsb[0]]);
	mutex_unlock(&data->update_lock);

	/* The LSB value is a 2-bit scaling of the MSB's LSbit value. */
	regval = (regval >> 6) * asc7621_in_scaling[nr] / (0xc0 << 2);

	return sprintf(buf, "%u\n", regval);
}