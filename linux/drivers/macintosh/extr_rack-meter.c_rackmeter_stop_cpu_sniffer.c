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
struct rackmeter {TYPE_1__* cpu; } ;
struct TYPE_2__ {int /*<<< orphan*/  sniffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rackmeter_stop_cpu_sniffer(struct rackmeter *rm)
{
	cancel_delayed_work_sync(&rm->cpu[0].sniffer);
	cancel_delayed_work_sync(&rm->cpu[1].sniffer);
}