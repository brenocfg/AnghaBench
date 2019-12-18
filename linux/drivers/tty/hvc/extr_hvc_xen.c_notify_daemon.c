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
struct xencons_info {int /*<<< orphan*/  evtchn; } ;

/* Variables and functions */
 int /*<<< orphan*/  notify_remote_via_evtchn (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void notify_daemon(struct xencons_info *cons)
{
	/* Use evtchn: this is called early, before irq is set up. */
	notify_remote_via_evtchn(cons->evtchn);
}