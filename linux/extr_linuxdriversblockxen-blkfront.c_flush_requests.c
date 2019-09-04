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
struct blkfront_ring_info {int /*<<< orphan*/  irq; int /*<<< orphan*/  ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  RING_PUSH_REQUESTS_AND_CHECK_NOTIFY (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  notify_remote_via_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void flush_requests(struct blkfront_ring_info *rinfo)
{
	int notify;

	RING_PUSH_REQUESTS_AND_CHECK_NOTIFY(&rinfo->ring, notify);

	if (notify)
		notify_remote_via_irq(rinfo->irq);
}