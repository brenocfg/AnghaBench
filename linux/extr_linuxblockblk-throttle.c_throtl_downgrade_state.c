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
struct throtl_data {int scale; int throtl_slice; int limit_index; void* low_downgrade_time; void* low_upgrade_time; int /*<<< orphan*/  service_queue; } ;

/* Variables and functions */
 void* jiffies ; 
 int /*<<< orphan*/  throtl_log (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static void throtl_downgrade_state(struct throtl_data *td, int new)
{
	td->scale /= 2;

	throtl_log(&td->service_queue, "downgrade, scale %d", td->scale);
	if (td->scale) {
		td->low_upgrade_time = jiffies - td->scale * td->throtl_slice;
		return;
	}

	td->limit_index = new;
	td->low_downgrade_time = jiffies;
}