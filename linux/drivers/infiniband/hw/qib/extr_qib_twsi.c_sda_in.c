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
typedef  int u8 ;
typedef  int u32 ;
struct qib_devdata {int gpio_sda_num; int (* f_gpio_mod ) (struct qib_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  i2c_wait_for_writes (struct qib_devdata*) ; 
 int stub1 (struct qib_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int stub2 (struct qib_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u8 sda_in(struct qib_devdata *dd, int wait)
{
	int bnum;
	u32 read_val, mask;

	bnum = dd->gpio_sda_num;
	mask = (1UL << bnum);
	/* SDA is meant to be bare-drain, so never set "OUT", just DIR */
	dd->f_gpio_mod(dd, 0, 0, mask);
	read_val = dd->f_gpio_mod(dd, 0, 0, 0);
	if (wait)
		i2c_wait_for_writes(dd);
	return (read_val & mask) >> bnum;
}