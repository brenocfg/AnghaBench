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
typedef  scalar_t__ u8 ;
typedef  unsigned long u32 ;
struct qib_devdata {unsigned long gpio_sda_num; int /*<<< orphan*/  (* f_gpio_mod ) (struct qib_devdata*,int /*<<< orphan*/ ,unsigned long,unsigned long) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  i2c_wait_for_writes (struct qib_devdata*) ; 
 int /*<<< orphan*/  stub1 (struct qib_devdata*,int /*<<< orphan*/ ,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void sda_out(struct qib_devdata *dd, u8 bit)
{
	u32 mask;

	mask = 1UL << dd->gpio_sda_num;

	/* SDA is meant to be bare-drain, so never set "OUT", just DIR */
	dd->f_gpio_mod(dd, 0, bit ? 0 : mask, mask);

	i2c_wait_for_writes(dd);
	udelay(2);
}