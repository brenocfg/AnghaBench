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
struct notifier_block {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  hw; } ;
struct TYPE_6__ {TYPE_1__ clkr; } ;
struct TYPE_5__ {int (* set_parent ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 unsigned long PRE_RATE_CHANGE ; 
 TYPE_3__ apps_clk_src ; 
 TYPE_2__ clk_rcg2_ops ; 
 int /*<<< orphan*/  gcc_ipq4019_cpu_safe_parent ; 
 int notifier_from_errno (int) ; 
 int stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
gcc_ipq4019_cpu_clk_notifier_fn(struct notifier_block *nb,
				unsigned long action, void *data)
{
	int err = 0;

	if (action == PRE_RATE_CHANGE)
		err = clk_rcg2_ops.set_parent(&apps_clk_src.clkr.hw,
					      gcc_ipq4019_cpu_safe_parent);

	return notifier_from_errno(err);
}