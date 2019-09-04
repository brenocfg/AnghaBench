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
struct notifier_block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  on_each_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stop_nmi_watchdog ; 

__attribute__((used)) static int nmi_shutdown(struct notifier_block *nb, unsigned long cmd, void *p)
{
	on_each_cpu(stop_nmi_watchdog, NULL, 1);
	return 0;
}