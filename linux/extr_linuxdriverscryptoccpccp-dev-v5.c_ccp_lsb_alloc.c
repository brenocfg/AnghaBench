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
struct ccp_device {scalar_t__ sb_avail; int /*<<< orphan*/  sb_queue; int /*<<< orphan*/  sb_mutex; int /*<<< orphan*/  lsbmap; } ;
struct ccp_cmd_queue {int lsb; struct ccp_device* ccp; int /*<<< orphan*/  lsbmap; } ;

/* Variables and functions */
 int LSB_SIZE ; 
 int MAX_LSB_CNT ; 
 scalar_t__ bitmap_find_next_zero_area (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_set (int /*<<< orphan*/ ,int,unsigned int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ wait_event_interruptible (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static u32 ccp_lsb_alloc(struct ccp_cmd_queue *cmd_q, unsigned int count)
{
	struct ccp_device *ccp;
	int start;

	/* First look at the map for the queue */
	if (cmd_q->lsb >= 0) {
		start = (u32)bitmap_find_next_zero_area(cmd_q->lsbmap,
							LSB_SIZE,
							0, count, 0);
		if (start < LSB_SIZE) {
			bitmap_set(cmd_q->lsbmap, start, count);
			return start + cmd_q->lsb * LSB_SIZE;
		}
	}

	/* No joy; try to get an entry from the shared blocks */
	ccp = cmd_q->ccp;
	for (;;) {
		mutex_lock(&ccp->sb_mutex);

		start = (u32)bitmap_find_next_zero_area(ccp->lsbmap,
							MAX_LSB_CNT * LSB_SIZE,
							0,
							count, 0);
		if (start <= MAX_LSB_CNT * LSB_SIZE) {
			bitmap_set(ccp->lsbmap, start, count);

			mutex_unlock(&ccp->sb_mutex);
			return start;
		}

		ccp->sb_avail = 0;

		mutex_unlock(&ccp->sb_mutex);

		/* Wait for KSB entries to become available */
		if (wait_event_interruptible(ccp->sb_queue, ccp->sb_avail))
			return 0;
	}
}