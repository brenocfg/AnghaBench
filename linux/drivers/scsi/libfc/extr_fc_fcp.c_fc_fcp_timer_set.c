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
struct fc_fcp_pkt {int state; unsigned long timer_delay; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int FC_SRB_COMPL ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void fc_fcp_timer_set(struct fc_fcp_pkt *fsp, unsigned long delay)
{
	if (!(fsp->state & FC_SRB_COMPL)) {
		mod_timer(&fsp->timer, jiffies + delay);
		fsp->timer_delay = delay;
	}
}