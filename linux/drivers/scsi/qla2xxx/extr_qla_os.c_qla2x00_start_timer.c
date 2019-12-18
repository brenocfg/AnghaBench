#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ expires; } ;
struct TYPE_5__ {int timer_active; TYPE_2__ timer; } ;
typedef  TYPE_1__ scsi_qla_host_t ;

/* Variables and functions */
 unsigned long HZ ; 
 int /*<<< orphan*/  add_timer (TYPE_2__*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  qla2x00_timer ; 
 int /*<<< orphan*/  timer_setup (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__inline__ void
qla2x00_start_timer(scsi_qla_host_t *vha, unsigned long interval)
{
	timer_setup(&vha->timer, qla2x00_timer, 0);
	vha->timer.expires = jiffies + interval * HZ;
	add_timer(&vha->timer);
	vha->timer_active = 1;
}