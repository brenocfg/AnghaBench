#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
struct TYPE_4__ {TYPE_1__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int nr_devs ; 
 TYPE_2__* stm_heartbeat ; 
 int /*<<< orphan*/  stm_source_unregister_device (TYPE_1__*) ; 

__attribute__((used)) static void stm_heartbeat_exit(void)
{
	int i;

	for (i = 0; i < nr_devs; i++) {
		stm_source_unregister_device(&stm_heartbeat[i].data);
		kfree(stm_heartbeat[i].data.name);
	}
}