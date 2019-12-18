#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct scsiio_tracker {int cb_idx; scalar_t__ smid; } ;
struct scsi_cmnd {int dummy; } ;
struct MPT3SAS_ADAPTER {scalar_t__ scsiio_depth; int /*<<< orphan*/  shost; } ;
struct TYPE_3__ {int /*<<< orphan*/  DevHandle; } ;
typedef  TYPE_1__ Mpi25SCSIIORequest_t ;

/* Variables and functions */
 scalar_t__ INTERNAL_SCSIIO_CMDS_COUNT ; 
 TYPE_1__* mpt3sas_base_get_msg_frame (struct MPT3SAS_ADAPTER*,scalar_t__) ; 
 struct scsiio_tracker* scsi_cmd_priv (struct scsi_cmnd*) ; 
 struct scsi_cmnd* scsi_host_find_tag (int /*<<< orphan*/ ,scalar_t__) ; 

struct scsi_cmnd *
mpt3sas_scsih_scsi_lookup_get(struct MPT3SAS_ADAPTER *ioc, u16 smid)
{
	struct scsi_cmnd *scmd = NULL;
	struct scsiio_tracker *st;
	Mpi25SCSIIORequest_t *mpi_request;

	if (smid > 0  &&
	    smid <= ioc->scsiio_depth - INTERNAL_SCSIIO_CMDS_COUNT) {
		u32 unique_tag = smid - 1;

		mpi_request = mpt3sas_base_get_msg_frame(ioc, smid);

		/*
		 * If SCSI IO request is outstanding at driver level then
		 * DevHandle filed must be non-zero. If DevHandle is zero
		 * then it means that this smid is free at driver level,
		 * so return NULL.
		 */
		if (!mpi_request->DevHandle)
			return scmd;

		scmd = scsi_host_find_tag(ioc->shost, unique_tag);
		if (scmd) {
			st = scsi_cmd_priv(scmd);
			if (st->cb_idx == 0xFF || st->smid == 0)
				scmd = NULL;
		}
	}
	return scmd;
}