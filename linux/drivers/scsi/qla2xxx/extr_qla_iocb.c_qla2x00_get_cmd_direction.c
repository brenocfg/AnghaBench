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
typedef  scalar_t__ uint16_t ;
struct TYPE_5__ {int /*<<< orphan*/  input_requests; int /*<<< orphan*/  input_bytes; int /*<<< orphan*/  output_requests; int /*<<< orphan*/  output_bytes; } ;
struct scsi_qla_host {TYPE_1__ qla_stats; } ;
struct scsi_cmnd {scalar_t__ sc_data_direction; } ;
struct TYPE_6__ {struct scsi_qla_host* vha; } ;
typedef  TYPE_2__ srb_t ;

/* Variables and functions */
 scalar_t__ CF_READ ; 
 scalar_t__ CF_WRITE ; 
 scalar_t__ DMA_FROM_DEVICE ; 
 scalar_t__ DMA_TO_DEVICE ; 
 struct scsi_cmnd* GET_CMD_SP (TYPE_2__*) ; 
 scalar_t__ scsi_bufflen (struct scsi_cmnd*) ; 

__attribute__((used)) static inline uint16_t
qla2x00_get_cmd_direction(srb_t *sp)
{
	uint16_t cflags;
	struct scsi_cmnd *cmd = GET_CMD_SP(sp);
	struct scsi_qla_host *vha = sp->vha;

	cflags = 0;

	/* Set transfer direction */
	if (cmd->sc_data_direction == DMA_TO_DEVICE) {
		cflags = CF_WRITE;
		vha->qla_stats.output_bytes += scsi_bufflen(cmd);
		vha->qla_stats.output_requests++;
	} else if (cmd->sc_data_direction == DMA_FROM_DEVICE) {
		cflags = CF_READ;
		vha->qla_stats.input_bytes += scsi_bufflen(cmd);
		vha->qla_stats.input_requests++;
	}
	return (cflags);
}