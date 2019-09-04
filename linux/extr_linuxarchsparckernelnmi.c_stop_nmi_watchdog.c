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
struct TYPE_2__ {int /*<<< orphan*/  pcr_nmi_disable; int /*<<< orphan*/  (* write_pcr ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  __this_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __this_cpu_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nmi_active ; 
 TYPE_1__* pcr_ops ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wd_enabled ; 

void stop_nmi_watchdog(void *unused)
{
	if (!__this_cpu_read(wd_enabled))
		return;
	pcr_ops->write_pcr(0, pcr_ops->pcr_nmi_disable);
	__this_cpu_write(wd_enabled, 0);
	atomic_dec(&nmi_active);
}