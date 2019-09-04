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
typedef  int u32 ;
struct ccp_device {int sb_count; scalar_t__ sb_avail; int /*<<< orphan*/  sb_queue; int /*<<< orphan*/  sb_mutex; int /*<<< orphan*/  sb; int /*<<< orphan*/  sb_start; } ;
struct ccp_cmd_queue {struct ccp_device* ccp; } ;

/* Variables and functions */
 int KSB_START ; 
 scalar_t__ bitmap_find_next_zero_area (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_set (int /*<<< orphan*/ ,int,unsigned int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ wait_event_interruptible (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static u32 ccp_alloc_ksb(struct ccp_cmd_queue *cmd_q, unsigned int count)
{
	int start;
	struct ccp_device *ccp = cmd_q->ccp;

	for (;;) {
		mutex_lock(&ccp->sb_mutex);

		start = (u32)bitmap_find_next_zero_area(ccp->sb,
							ccp->sb_count,
							ccp->sb_start,
							count, 0);
		if (start <= ccp->sb_count) {
			bitmap_set(ccp->sb, start, count);

			mutex_unlock(&ccp->sb_mutex);
			break;
		}

		ccp->sb_avail = 0;

		mutex_unlock(&ccp->sb_mutex);

		/* Wait for KSB entries to become available */
		if (wait_event_interruptible(ccp->sb_queue, ccp->sb_avail))
			return 0;
	}

	return KSB_START + start;
}