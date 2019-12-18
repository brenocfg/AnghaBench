#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct nvram {TYPE_8__* bus; } ;
struct scsi_qla_host {struct nvram nvram; } ;
struct TYPE_16__ {TYPE_7__* target; scalar_t__ max_queue_depth; } ;
struct TYPE_13__ {int device_enable; int sync_offset; } ;
struct TYPE_10__ {int device_enable; int sync_offset; } ;
struct TYPE_14__ {TYPE_5__ flags1x80; TYPE_2__ flags1x160; } ;
struct TYPE_11__ {int enable_ppr; int ppr_options; int ppr_bus_width; } ;
struct TYPE_12__ {TYPE_3__ flags; } ;
struct TYPE_9__ {int renegotiate_on_error; int auto_request_sense; int tag_queuing; int enable_sync; int enable_wide; int parity_checking; int disconnect_allowed; } ;
struct TYPE_15__ {int sync_period; TYPE_6__ flags; TYPE_4__ ppr_1x160; TYPE_1__ parameter; scalar_t__ execution_throttle; } ;

/* Variables and functions */
 scalar_t__ IS_ISP1x160 (struct scsi_qla_host*) ; 

__attribute__((used)) static void
qla1280_set_target_defaults(struct scsi_qla_host *ha, int bus, int target)
{
	struct nvram *nv = &ha->nvram;

	nv->bus[bus].target[target].parameter.renegotiate_on_error = 1;
	nv->bus[bus].target[target].parameter.auto_request_sense = 1;
	nv->bus[bus].target[target].parameter.tag_queuing = 1;
	nv->bus[bus].target[target].parameter.enable_sync = 1;
#if 1	/* Some SCSI Processors do not seem to like this */
	nv->bus[bus].target[target].parameter.enable_wide = 1;
#endif
	nv->bus[bus].target[target].execution_throttle =
		nv->bus[bus].max_queue_depth - 1;
	nv->bus[bus].target[target].parameter.parity_checking = 1;
	nv->bus[bus].target[target].parameter.disconnect_allowed = 1;

	if (IS_ISP1x160(ha)) {
		nv->bus[bus].target[target].flags.flags1x160.device_enable = 1;
		nv->bus[bus].target[target].flags.flags1x160.sync_offset = 0x0e;
		nv->bus[bus].target[target].sync_period = 9;
		nv->bus[bus].target[target].ppr_1x160.flags.enable_ppr = 1;
		nv->bus[bus].target[target].ppr_1x160.flags.ppr_options = 2;
		nv->bus[bus].target[target].ppr_1x160.flags.ppr_bus_width = 1;
	} else {
		nv->bus[bus].target[target].flags.flags1x80.device_enable = 1;
		nv->bus[bus].target[target].flags.flags1x80.sync_offset = 12;
		nv->bus[bus].target[target].sync_period = 10;
	}
}