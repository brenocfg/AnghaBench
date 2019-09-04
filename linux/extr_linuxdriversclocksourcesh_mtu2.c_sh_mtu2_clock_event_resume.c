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
struct clock_event_device {int dummy; } ;
struct TYPE_6__ {TYPE_2__* mtu; } ;
struct TYPE_5__ {TYPE_1__* pdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 TYPE_3__* ced_to_sh_mtu2 (struct clock_event_device*) ; 
 int /*<<< orphan*/  pm_genpd_syscore_poweron (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sh_mtu2_clock_event_resume(struct clock_event_device *ced)
{
	pm_genpd_syscore_poweron(&ced_to_sh_mtu2(ced)->mtu->pdev->dev);
}