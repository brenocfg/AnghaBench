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
struct adb_request {struct adb_request* next; } ;

/* Variables and functions */
 struct adb_request* current_req ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 

__attribute__((used)) static int request_is_queued(struct adb_request *req) {
	struct adb_request *cur;
	unsigned long flags;
	local_irq_save(flags);
	cur = current_req;
	while (cur) {
		if (cur == req) {
			local_irq_restore(flags);
			return 1;
		}
		cur = cur->next;
	}
	local_irq_restore(flags);
	return 0;
}