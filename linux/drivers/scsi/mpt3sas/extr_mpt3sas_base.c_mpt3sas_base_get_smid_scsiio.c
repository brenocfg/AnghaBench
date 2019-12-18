#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  unsigned int u16 ;
struct scsiio_tracker {unsigned int smid; int /*<<< orphan*/  chain_list; struct scsi_cmnd* scmd; int /*<<< orphan*/  cb_idx; } ;
struct scsi_cmnd {TYPE_1__* request; } ;
struct MPT3SAS_ADAPTER {int dummy; } ;
struct TYPE_2__ {unsigned int tag; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct scsiio_tracker* scsi_cmd_priv (struct scsi_cmnd*) ; 

u16
mpt3sas_base_get_smid_scsiio(struct MPT3SAS_ADAPTER *ioc, u8 cb_idx,
	struct scsi_cmnd *scmd)
{
	struct scsiio_tracker *request = scsi_cmd_priv(scmd);
	unsigned int tag = scmd->request->tag;
	u16 smid;

	smid = tag + 1;
	request->cb_idx = cb_idx;
	request->smid = smid;
	request->scmd = scmd;
	INIT_LIST_HEAD(&request->chain_list);
	return smid;
}