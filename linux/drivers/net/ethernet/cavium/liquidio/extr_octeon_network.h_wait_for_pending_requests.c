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
struct octeon_device {TYPE_1__* response_list; } ;
struct TYPE_2__ {int /*<<< orphan*/  pending_req_count; } ;

/* Variables and functions */
 int HZ ; 
 int MAX_IO_PENDING_PKT_COUNT ; 
 size_t OCTEON_ORDERED_SC_LIST ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_timeout_uninterruptible (int) ; 

__attribute__((used)) static inline int wait_for_pending_requests(struct octeon_device *oct)
{
	int i, pcount = 0;

	for (i = 0; i < MAX_IO_PENDING_PKT_COUNT; i++) {
		pcount = atomic_read(
		    &oct->response_list[OCTEON_ORDERED_SC_LIST]
			 .pending_req_count);
		if (pcount)
			schedule_timeout_uninterruptible(HZ / 10);
		else
			break;
	}

	if (pcount)
		return 1;

	return 0;
}