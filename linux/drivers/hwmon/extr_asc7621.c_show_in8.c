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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_6__ {int* reg; } ;
struct TYPE_5__ {size_t* msb; } ;
struct TYPE_4__ {size_t index; } ;

/* Variables and functions */
 int /*<<< orphan*/  SETUP_SHOW_DATA_PARAM (struct device*,struct device_attribute*) ; 
 int* asc7621_in_scaling ; 
 TYPE_3__* data ; 
 TYPE_2__* param ; 
 TYPE_1__* sda ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t show_in8(struct device *dev, struct device_attribute *attr,
			char *buf)
{
	SETUP_SHOW_DATA_PARAM(dev, attr);
	u8 nr = sda->index;

	return sprintf(buf, "%u\n",
		       ((data->reg[param->msb[0]] *
			 asc7621_in_scaling[nr]) / 0xc0));
}