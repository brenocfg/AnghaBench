#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct scsiio_tracker {int direct_io; } ;
struct scsi_cmnd {scalar_t__* cmnd; } ;
struct _raid_device {int block_exponent; int max_lba; int stripe_sz; int stripe_exponent; scalar_t__ num_pds; int /*<<< orphan*/ * pd_handle; } ;
struct MPT3SAS_ADAPTER {int dummy; } ;
typedef  int sector_t ;
struct TYPE_4__ {int /*<<< orphan*/ * CDB32; } ;
struct TYPE_5__ {TYPE_1__ CDB; int /*<<< orphan*/  DevHandle; } ;
typedef  TYPE_2__ Mpi25SCSIIORequest_t ;

/* Variables and functions */
 scalar_t__ READ_10 ; 
 scalar_t__ READ_16 ; 
 scalar_t__ WRITE_10 ; 
 scalar_t__ WRITE_16 ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int get_unaligned_be32 (int /*<<< orphan*/ *) ; 
 int get_unaligned_be64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lower_32_bits (int) ; 
 int /*<<< orphan*/  put_unaligned_be32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_unaligned_be64 (int,int /*<<< orphan*/ *) ; 
 int scsi_bufflen (struct scsi_cmnd*) ; 
 struct scsiio_tracker* scsi_cmd_priv (struct scsi_cmnd*) ; 
 int sector_div (int,scalar_t__) ; 

void
mpt3sas_setup_direct_io(struct MPT3SAS_ADAPTER *ioc, struct scsi_cmnd *scmd,
	struct _raid_device *raid_device, Mpi25SCSIIORequest_t *mpi_request)
{
	sector_t v_lba, p_lba, stripe_off, column, io_size;
	u32 stripe_sz, stripe_exp;
	u8 num_pds, cmd = scmd->cmnd[0];
	struct scsiio_tracker *st = scsi_cmd_priv(scmd);

	if (cmd != READ_10 && cmd != WRITE_10 &&
	    cmd != READ_16 && cmd != WRITE_16)
		return;

	if (cmd == READ_10 || cmd == WRITE_10)
		v_lba = get_unaligned_be32(&mpi_request->CDB.CDB32[2]);
	else
		v_lba = get_unaligned_be64(&mpi_request->CDB.CDB32[2]);

	io_size = scsi_bufflen(scmd) >> raid_device->block_exponent;

	if (v_lba + io_size - 1 > raid_device->max_lba)
		return;

	stripe_sz = raid_device->stripe_sz;
	stripe_exp = raid_device->stripe_exponent;
	stripe_off = v_lba & (stripe_sz - 1);

	/* Return unless IO falls within a stripe */
	if (stripe_off + io_size > stripe_sz)
		return;

	num_pds = raid_device->num_pds;
	p_lba = v_lba >> stripe_exp;
	column = sector_div(p_lba, num_pds);
	p_lba = (p_lba << stripe_exp) + stripe_off;
	mpi_request->DevHandle = cpu_to_le16(raid_device->pd_handle[column]);

	if (cmd == READ_10 || cmd == WRITE_10)
		put_unaligned_be32(lower_32_bits(p_lba),
				   &mpi_request->CDB.CDB32[2]);
	else
		put_unaligned_be64(p_lba, &mpi_request->CDB.CDB32[2]);

	st->direct_io = 1;
}