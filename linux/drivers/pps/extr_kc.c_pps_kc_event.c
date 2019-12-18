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
struct pps_event_time {int /*<<< orphan*/  ts_raw; int /*<<< orphan*/  ts_real; } ;
struct pps_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hardpps (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct pps_device* pps_kc_hardpps_dev ; 
 int /*<<< orphan*/  pps_kc_hardpps_lock ; 
 int pps_kc_hardpps_mode ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void pps_kc_event(struct pps_device *pps, struct pps_event_time *ts,
		int event)
{
	unsigned long flags;

	/* Pass some events to kernel consumer if activated */
	spin_lock_irqsave(&pps_kc_hardpps_lock, flags);
	if (pps == pps_kc_hardpps_dev && event & pps_kc_hardpps_mode)
		hardpps(&ts->ts_real, &ts->ts_raw);
	spin_unlock_irqrestore(&pps_kc_hardpps_lock, flags);
}