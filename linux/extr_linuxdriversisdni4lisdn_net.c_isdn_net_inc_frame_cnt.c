#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  frame_cnt; } ;
typedef  TYPE_1__ isdn_net_local ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ isdn_net_device_busy (TYPE_1__*) ; 
 int /*<<< orphan*/  isdn_net_device_stop_queue (TYPE_1__*) ; 

__attribute__((used)) static __inline__ void isdn_net_inc_frame_cnt(isdn_net_local *lp)
{
	atomic_inc(&lp->frame_cnt);
	if (isdn_net_device_busy(lp))
		isdn_net_device_stop_queue(lp);
}