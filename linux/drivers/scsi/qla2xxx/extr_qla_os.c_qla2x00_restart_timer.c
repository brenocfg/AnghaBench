#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int device_flags; int /*<<< orphan*/  timer; } ;
typedef  TYPE_1__ scsi_qla_host_t ;

/* Variables and functions */
 int DFLG_DEV_FAILED ; 
 unsigned long HZ ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,TYPE_1__*,int,char*) ; 
 int /*<<< orphan*/  ql_dbg_timer ; 

__attribute__((used)) static inline void
qla2x00_restart_timer(scsi_qla_host_t *vha, unsigned long interval)
{
	/* Currently used for 82XX only. */
	if (vha->device_flags & DFLG_DEV_FAILED) {
		ql_dbg(ql_dbg_timer, vha, 0x600d,
		    "Device in a failed state, returning.\n");
		return;
	}

	mod_timer(&vha->timer, jiffies + interval * HZ);
}