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
typedef  int u32 ;
struct qib_devdata {unsigned long gpio_scl_num; int (* f_gpio_mod ) (struct qib_devdata*,int /*<<< orphan*/ ,int,int) ;} ;

/* Variables and functions */
 int SCL_WAIT_USEC ; 
 int /*<<< orphan*/  i2c_wait_for_writes (struct qib_devdata*) ; 
 int /*<<< orphan*/  qib_dev_err (struct qib_devdata*,char*,int) ; 
 int stub1 (struct qib_devdata*,int /*<<< orphan*/ ,int,int) ; 
 int stub2 (struct qib_devdata*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void scl_out(struct qib_devdata *dd, u8 bit)
{
	u32 mask;

	udelay(1);

	mask = 1UL << dd->gpio_scl_num;

	/* SCL is meant to be bare-drain, so never set "OUT", just DIR */
	dd->f_gpio_mod(dd, 0, bit ? 0 : mask, mask);

	/*
	 * Allow for slow slaves by simple
	 * delay for falling edge, sampling on rise.
	 */
	if (!bit)
		udelay(2);
	else {
		int rise_usec;

		for (rise_usec = SCL_WAIT_USEC; rise_usec > 0; rise_usec -= 2) {
			if (mask & dd->f_gpio_mod(dd, 0, 0, 0))
				break;
			udelay(2);
		}
		if (rise_usec <= 0)
			qib_dev_err(dd, "SCL interface stuck low > %d uSec\n",
				    SCL_WAIT_USEC);
	}
	i2c_wait_for_writes(dd);
}