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
struct TYPE_2__ {int /*<<< orphan*/  (* disable ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  irqs_disabled () ; 
 int num_online_cpus () ; 
 TYPE_1__ outer_cache ; 
 int /*<<< orphan*/  stub1 () ; 

void outer_disable(void)
{
	WARN_ON(!irqs_disabled());
	WARN_ON(num_online_cpus() > 1);

	if (outer_cache.disable)
		outer_cache.disable();
}