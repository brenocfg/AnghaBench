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
struct qib_devdata {int /*<<< orphan*/  (* f_gpio_mod ) (struct qib_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  rmb () ; 
 int /*<<< orphan*/  stub1 (struct qib_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i2c_wait_for_writes(struct qib_devdata *dd)
{
	/*
	 * implicit read of EXTStatus is as good as explicit
	 * read of scratch, if all we want to do is flush
	 * writes.
	 */
	dd->f_gpio_mod(dd, 0, 0, 0);
	rmb(); /* inlined, so prevent compiler reordering */
}