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
struct TYPE_2__ {scalar_t__ flags; } ;
struct test_probe {int registered; TYPE_1__ kprobe; } ;

/* Variables and functions */
 int /*<<< orphan*/  unregister_kprobe (TYPE_1__*) ; 

__attribute__((used)) static void unregister_test_probe(struct test_probe *probe)
{
	if (probe->registered) {
		unregister_kprobe(&probe->kprobe);
		probe->kprobe.flags = 0; /* Clear disable flag to allow reuse */
	}
	probe->registered = false;
}