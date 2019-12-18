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
typedef  int u8 ;
struct TYPE_6__ {TYPE_2__* red_balance; TYPE_1__* blue_balance; } ;
struct ov965x {TYPE_3__ ctrls; } ;
struct TYPE_5__ {int val; } ;
struct TYPE_4__ {int val; } ;

/* Variables and functions */
 int REG_BLUE ; 
 int REG_COM8 ; 
 int REG_RED ; 
 int ov965x_read (struct ov965x*,int,int*) ; 
 int ov965x_write (struct ov965x*,int,int) ; 

__attribute__((used)) static int ov965x_set_white_balance(struct ov965x *ov965x, int awb)
{
	int ret;
	u8 reg;

	ret = ov965x_read(ov965x, REG_COM8, &reg);
	if (!ret) {
		reg = awb ? reg | REG_COM8 : reg & ~REG_COM8;
		ret = ov965x_write(ov965x, REG_COM8, reg);
	}
	if (!ret && !awb) {
		ret = ov965x_write(ov965x, REG_BLUE,
				   ov965x->ctrls.blue_balance->val);
		if (ret < 0)
			return ret;
		ret = ov965x_write(ov965x, REG_RED,
				   ov965x->ctrls.red_balance->val);
	}
	return ret;
}