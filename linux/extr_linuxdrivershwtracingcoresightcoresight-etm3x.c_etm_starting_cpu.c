#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int os_unlock; int /*<<< orphan*/  spinlock; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  etm_enable_hw (TYPE_1__*) ; 
 int /*<<< orphan*/  etm_os_unlock (TYPE_1__*) ; 
 TYPE_1__** etmdrvdata ; 
 scalar_t__ local_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int etm_starting_cpu(unsigned int cpu)
{
	if (!etmdrvdata[cpu])
		return 0;

	spin_lock(&etmdrvdata[cpu]->spinlock);
	if (!etmdrvdata[cpu]->os_unlock) {
		etm_os_unlock(etmdrvdata[cpu]);
		etmdrvdata[cpu]->os_unlock = true;
	}

	if (local_read(&etmdrvdata[cpu]->mode))
		etm_enable_hw(etmdrvdata[cpu]);
	spin_unlock(&etmdrvdata[cpu]->spinlock);
	return 0;
}