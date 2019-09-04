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
struct ivtv_mailbox_data {int max_mbox; } ;
struct ivtv {int dummy; } ;

/* Variables and functions */
 int API_FAST_RESULT ; 
 int API_NO_WAIT_MB ; 
 int API_RESULT ; 
 int ENODEV ; 
 int /*<<< orphan*/  ivtv_msleep_timeout (int,int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 scalar_t__ time_after (unsigned long,scalar_t__) ; 
 scalar_t__ try_mailbox (struct ivtv*,struct ivtv_mailbox_data*,int) ; 

__attribute__((used)) static int get_mailbox(struct ivtv *itv, struct ivtv_mailbox_data *mbdata, int flags)
{
	unsigned long then = jiffies;
	int i, mb;
	int max_mbox = mbdata->max_mbox;
	int retries = 100;

	/* All slow commands use the same mailbox, serializing them and also
	   leaving the other mailbox free for simple fast commands. */
	if ((flags & API_FAST_RESULT) == API_RESULT)
		max_mbox = 1;

	/* find free non-DMA mailbox */
	for (i = 0; i < retries; i++) {
		for (mb = 1; mb <= max_mbox; mb++)
			if (try_mailbox(itv, mbdata, mb))
				return mb;

		/* Sleep before a retry, if not atomic */
		if (!(flags & API_NO_WAIT_MB)) {
			if (time_after(jiffies,
				       then + msecs_to_jiffies(10*retries)))
			       break;
			ivtv_msleep_timeout(10, 0);
		}
	}
	return -ENODEV;
}