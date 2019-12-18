#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int burst_enable; int fifo_threshold; } ;
struct TYPE_10__ {int scsi_bus_0_control; int scsi_bus_1_control; int auto_term_support; } ;
struct TYPE_8__ {int enable_fast_posting; int disable_synchronous_backoff; } ;
struct TYPE_9__ {TYPE_1__ f; } ;
struct nvram {int isp_parameter; TYPE_7__* bus; TYPE_4__ isp_config; TYPE_3__ termination; TYPE_2__ firmware_feature; } ;
struct scsi_qla_host {struct nvram nvram; } ;
struct TYPE_13__ {int req_ack_active_negation; int data_line_active_negation; int async_data_setup_time; } ;
struct TYPE_12__ {int initiator_id; } ;
struct TYPE_14__ {int selection_timeout; int max_queue_depth; int bus_reset_delay; int retry_delay; TYPE_6__ config_2; TYPE_5__ config_1; } ;

/* Variables and functions */
 scalar_t__ IS_ISP1040 (struct scsi_qla_host*) ; 
 scalar_t__ IS_ISP1x160 (struct scsi_qla_host*) ; 
 int MAX_BUSES ; 
 int MAX_TARGETS ; 
 int /*<<< orphan*/  dprintk (int,char*) ; 
 int /*<<< orphan*/  memset (struct nvram*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qla1280_set_target_defaults (struct scsi_qla_host*,int,int) ; 

__attribute__((used)) static void
qla1280_set_defaults(struct scsi_qla_host *ha)
{
	struct nvram *nv = &ha->nvram;
	int bus, target;

	dprintk(1, "Using defaults for NVRAM: \n");
	memset(nv, 0, sizeof(struct nvram));

	/* nv->cntr_flags_1.disable_loading_risc_code = 1; */
	nv->firmware_feature.f.enable_fast_posting = 1;
	nv->firmware_feature.f.disable_synchronous_backoff = 1;
	nv->termination.scsi_bus_0_control = 3;
	nv->termination.scsi_bus_1_control = 3;
	nv->termination.auto_term_support = 1;

	/*
	 * Set default FIFO magic - What appropriate values would be here
	 * is unknown. This is what I have found testing with 12160s.
	 *
	 * Now, I would love the magic decoder ring for this one, the
	 * header file provided by QLogic seems to be bogus or incomplete
	 * at best.
	 */
	nv->isp_config.burst_enable = 1;
	if (IS_ISP1040(ha))
		nv->isp_config.fifo_threshold |= 3;
	else
		nv->isp_config.fifo_threshold |= 4;

	if (IS_ISP1x160(ha))
		nv->isp_parameter = 0x01; /* fast memory enable */

	for (bus = 0; bus < MAX_BUSES; bus++) {
		nv->bus[bus].config_1.initiator_id = 7;
		nv->bus[bus].config_2.req_ack_active_negation = 1;
		nv->bus[bus].config_2.data_line_active_negation = 1;
		nv->bus[bus].selection_timeout = 250;
		nv->bus[bus].max_queue_depth = 32;

		if (IS_ISP1040(ha)) {
			nv->bus[bus].bus_reset_delay = 3;
			nv->bus[bus].config_2.async_data_setup_time = 6;
			nv->bus[bus].retry_delay = 1;
		} else {
			nv->bus[bus].bus_reset_delay = 5;
			nv->bus[bus].config_2.async_data_setup_time = 8;
		}

		for (target = 0; target < MAX_TARGETS; target++)
			qla1280_set_target_defaults(ha, bus, target);
	}
}