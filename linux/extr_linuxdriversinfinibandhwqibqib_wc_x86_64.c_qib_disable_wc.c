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
struct qib_devdata {int /*<<< orphan*/  wc_cookie; } ;

/* Variables and functions */
 int /*<<< orphan*/  arch_phys_wc_del (int /*<<< orphan*/ ) ; 

void qib_disable_wc(struct qib_devdata *dd)
{
	arch_phys_wc_del(dd->wc_cookie);
}