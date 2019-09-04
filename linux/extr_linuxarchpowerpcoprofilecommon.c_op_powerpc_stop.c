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
struct TYPE_2__ {int /*<<< orphan*/  (* global_stop ) () ;scalar_t__ stop; } ;

/* Variables and functions */
 TYPE_1__* model ; 
 int /*<<< orphan*/  on_each_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  op_powerpc_cpu_stop ; 
 int /*<<< orphan*/  stub1 () ; 

__attribute__((used)) static void op_powerpc_stop(void)
{
	if (model->stop)
		on_each_cpu(op_powerpc_cpu_stop, NULL, 1);
        if (model->global_stop)
                model->global_stop();
}