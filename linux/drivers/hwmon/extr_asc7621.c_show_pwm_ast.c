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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_4__ {size_t* reg; } ;
struct TYPE_3__ {size_t* msb; size_t* shift; size_t* mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  SETUP_SHOW_DATA_PARAM (struct device*,struct device_attribute*) ; 
 int* asc7621_pwm_auto_spinup_map ; 
 size_t clamp_val (size_t,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* data ; 
 TYPE_1__* param ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t show_pwm_ast(struct device *dev,
			    struct device_attribute *attr, char *buf)
{
	SETUP_SHOW_DATA_PARAM(dev, attr);
	u8 regval =
	    (data->reg[param->msb[0]] >> param->shift[0]) & param->mask[0];

	regval = clamp_val(regval, 0, 7);

	return sprintf(buf, "%u\n", asc7621_pwm_auto_spinup_map[regval]);

}