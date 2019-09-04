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
struct subch_data_s {int /*<<< orphan*/  sd_rlock; int /*<<< orphan*/  sd_rb; int /*<<< orphan*/  sd_subch; int /*<<< orphan*/  sd_nasid; } ;

/* Variables and functions */
 int CHUNKSIZE ; 
 struct subch_data_s* event_sd ; 
 int ia64_sn_irtr_recv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  scdrv_dispatch_event (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void
scdrv_event(unsigned long dummy)
{
	int status;
	int len;
	unsigned long flags;
	struct subch_data_s *sd = event_sd;

	/* anything to read? */
	len = CHUNKSIZE;
	spin_lock_irqsave(&sd->sd_rlock, flags);
	status = ia64_sn_irtr_recv(sd->sd_nasid, sd->sd_subch,
				   sd->sd_rb, &len);

	while (!(status < 0)) {
		spin_unlock_irqrestore(&sd->sd_rlock, flags);
		scdrv_dispatch_event(sd->sd_rb, len);
		len = CHUNKSIZE;
		spin_lock_irqsave(&sd->sd_rlock, flags);
		status = ia64_sn_irtr_recv(sd->sd_nasid, sd->sd_subch,
					   sd->sd_rb, &len);
	}
	spin_unlock_irqrestore(&sd->sd_rlock, flags);
}