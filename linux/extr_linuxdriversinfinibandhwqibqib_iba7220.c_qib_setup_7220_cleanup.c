#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct qib_devdata {TYPE_1__* cspec; } ;
struct TYPE_2__ {int /*<<< orphan*/  portcntrs; int /*<<< orphan*/  cntrs; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qib_free_irq (struct qib_devdata*) ; 

__attribute__((used)) static void qib_setup_7220_cleanup(struct qib_devdata *dd)
{
	qib_free_irq(dd);
	kfree(dd->cspec->cntrs);
	kfree(dd->cspec->portcntrs);
}