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
struct event_arg {int /*<<< orphan*/  fcport; } ;
typedef  int /*<<< orphan*/  scsi_qla_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  qla24xx_post_gnl_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void qla24xx_handle_gnnid_event(scsi_qla_host_t *vha, struct event_arg *ea)
{
	qla24xx_post_gnl_work(vha, ea->fcport);
}