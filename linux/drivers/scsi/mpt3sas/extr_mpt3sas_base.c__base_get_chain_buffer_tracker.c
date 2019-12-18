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
typedef  size_t u8 ;
typedef  int u16 ;
struct scsiio_tracker {int smid; } ;
struct scsi_cmnd {int dummy; } ;
struct chain_tracker {int dummy; } ;
struct MPT3SAS_ADAPTER {size_t chains_needed_per_io; TYPE_1__* chain_lookup; } ;
struct TYPE_2__ {int /*<<< orphan*/  chain_offset; struct chain_tracker* chains_per_smid; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 size_t atomic_read (int /*<<< orphan*/ *) ; 
 struct scsiio_tracker* scsi_cmd_priv (struct scsi_cmnd*) ; 

__attribute__((used)) static struct chain_tracker *
_base_get_chain_buffer_tracker(struct MPT3SAS_ADAPTER *ioc,
			       struct scsi_cmnd *scmd)
{
	struct chain_tracker *chain_req;
	struct scsiio_tracker *st = scsi_cmd_priv(scmd);
	u16 smid = st->smid;
	u8 chain_offset =
	   atomic_read(&ioc->chain_lookup[smid - 1].chain_offset);

	if (chain_offset == ioc->chains_needed_per_io)
		return NULL;

	chain_req = &ioc->chain_lookup[smid - 1].chains_per_smid[chain_offset];
	atomic_inc(&ioc->chain_lookup[smid - 1].chain_offset);
	return chain_req;
}