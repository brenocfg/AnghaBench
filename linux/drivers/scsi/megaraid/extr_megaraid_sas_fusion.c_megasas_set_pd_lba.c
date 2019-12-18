#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u64 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct scsi_cmnd {scalar_t__ sc_data_direction; TYPE_2__* device; } ;
struct TYPE_8__ {scalar_t__ ldPiMode; } ;
struct MR_LD_RAID {TYPE_4__ capability; } ;
struct MR_DRV_RAID_MAP_ALL {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  PrimaryApplicationTagMask; int /*<<< orphan*/  PrimaryReferenceTag; } ;
struct TYPE_7__ {int* CDB32; TYPE_1__ EEDP32; } ;
struct MPI2_RAID_SCSI_IO_REQUEST {void* IoFlags; int /*<<< orphan*/  EEDPBlockSize; int /*<<< orphan*/  Control; void* EEDPFlags; TYPE_3__ CDB; } ;
struct IO_REQUEST_INFO {int pdBlock; int numBlocks; int /*<<< orphan*/  ldTgtId; } ;
struct TYPE_6__ {int sector_size; } ;

/* Variables and functions */
 scalar_t__ DMA_FROM_DEVICE ; 
 int MEGASAS_RD_WR_PROTECT_CHECK_ALL ; 
 int MEGASAS_SCSI_ADDL_CDB_LEN ; 
 int MEGASAS_SCSI_SERVICE_ACTION_READ32 ; 
 int MEGASAS_SCSI_SERVICE_ACTION_WRITE32 ; 
 int MEGASAS_SCSI_VARIABLE_LENGTH_CMD ; 
 int MPI25_SCSIIO_EEDPFLAGS_DO_NOT_DISABLE_MODE ; 
 int MPI2_SCSIIO_EEDPFLAGS_CHECK_APPTAG ; 
 int MPI2_SCSIIO_EEDPFLAGS_CHECK_GUARD ; 
 int MPI2_SCSIIO_EEDPFLAGS_CHECK_REFTAG ; 
 int MPI2_SCSIIO_EEDPFLAGS_CHECK_REMOVE_OP ; 
 int MPI2_SCSIIO_EEDPFLAGS_INC_PRI_REFTAG ; 
 int MPI2_SCSIIO_EEDPFLAGS_INSERT_OP ; 
 struct MR_LD_RAID* MR_LdRaidGet (int /*<<< orphan*/ ,struct MR_DRV_RAID_MAP_ALL*) ; 
 scalar_t__ MR_PROT_INFO_TYPE_CONTROLLER ; 
 int /*<<< orphan*/  MR_TargetIdToLdGet (int /*<<< orphan*/ ,struct MR_DRV_RAID_MAP_ALL*) ; 
 int READ_10 ; 
 int READ_12 ; 
 int READ_16 ; 
 int READ_6 ; 
 int WRITE_10 ; 
 int WRITE_16 ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
megasas_set_pd_lba(struct MPI2_RAID_SCSI_IO_REQUEST *io_request, u8 cdb_len,
		   struct IO_REQUEST_INFO *io_info, struct scsi_cmnd *scp,
		   struct MR_DRV_RAID_MAP_ALL *local_map_ptr, u32 ref_tag)
{
	struct MR_LD_RAID *raid;
	u16 ld;
	u64 start_blk = io_info->pdBlock;
	u8 *cdb = io_request->CDB.CDB32;
	u32 num_blocks = io_info->numBlocks;
	u8 opcode = 0, flagvals = 0, groupnum = 0, control = 0;

	/* Check if T10 PI (DIF) is enabled for this LD */
	ld = MR_TargetIdToLdGet(io_info->ldTgtId, local_map_ptr);
	raid = MR_LdRaidGet(ld, local_map_ptr);
	if (raid->capability.ldPiMode == MR_PROT_INFO_TYPE_CONTROLLER) {
		memset(cdb, 0, sizeof(io_request->CDB.CDB32));
		cdb[0] =  MEGASAS_SCSI_VARIABLE_LENGTH_CMD;
		cdb[7] =  MEGASAS_SCSI_ADDL_CDB_LEN;

		if (scp->sc_data_direction == DMA_FROM_DEVICE)
			cdb[9] = MEGASAS_SCSI_SERVICE_ACTION_READ32;
		else
			cdb[9] = MEGASAS_SCSI_SERVICE_ACTION_WRITE32;
		cdb[10] = MEGASAS_RD_WR_PROTECT_CHECK_ALL;

		/* LBA */
		cdb[12] = (u8)((start_blk >> 56) & 0xff);
		cdb[13] = (u8)((start_blk >> 48) & 0xff);
		cdb[14] = (u8)((start_blk >> 40) & 0xff);
		cdb[15] = (u8)((start_blk >> 32) & 0xff);
		cdb[16] = (u8)((start_blk >> 24) & 0xff);
		cdb[17] = (u8)((start_blk >> 16) & 0xff);
		cdb[18] = (u8)((start_blk >> 8) & 0xff);
		cdb[19] = (u8)(start_blk & 0xff);

		/* Logical block reference tag */
		io_request->CDB.EEDP32.PrimaryReferenceTag =
			cpu_to_be32(ref_tag);
		io_request->CDB.EEDP32.PrimaryApplicationTagMask = cpu_to_be16(0xffff);
		io_request->IoFlags = cpu_to_le16(32); /* Specify 32-byte cdb */

		/* Transfer length */
		cdb[28] = (u8)((num_blocks >> 24) & 0xff);
		cdb[29] = (u8)((num_blocks >> 16) & 0xff);
		cdb[30] = (u8)((num_blocks >> 8) & 0xff);
		cdb[31] = (u8)(num_blocks & 0xff);

		/* set SCSI IO EEDPFlags */
		if (scp->sc_data_direction == DMA_FROM_DEVICE) {
			io_request->EEDPFlags = cpu_to_le16(
				MPI2_SCSIIO_EEDPFLAGS_INC_PRI_REFTAG  |
				MPI2_SCSIIO_EEDPFLAGS_CHECK_REFTAG |
				MPI2_SCSIIO_EEDPFLAGS_CHECK_REMOVE_OP |
				MPI2_SCSIIO_EEDPFLAGS_CHECK_APPTAG |
				MPI25_SCSIIO_EEDPFLAGS_DO_NOT_DISABLE_MODE |
				MPI2_SCSIIO_EEDPFLAGS_CHECK_GUARD);
		} else {
			io_request->EEDPFlags = cpu_to_le16(
				MPI2_SCSIIO_EEDPFLAGS_INC_PRI_REFTAG |
				MPI2_SCSIIO_EEDPFLAGS_INSERT_OP);
		}
		io_request->Control |= cpu_to_le32((0x4 << 26));
		io_request->EEDPBlockSize = cpu_to_le32(scp->device->sector_size);
	} else {
		/* Some drives don't support 16/12 byte CDB's, convert to 10 */
		if (((cdb_len == 12) || (cdb_len == 16)) &&
		    (start_blk <= 0xffffffff)) {
			if (cdb_len == 16) {
				opcode = cdb[0] == READ_16 ? READ_10 : WRITE_10;
				flagvals = cdb[1];
				groupnum = cdb[14];
				control = cdb[15];
			} else {
				opcode = cdb[0] == READ_12 ? READ_10 : WRITE_10;
				flagvals = cdb[1];
				groupnum = cdb[10];
				control = cdb[11];
			}

			memset(cdb, 0, sizeof(io_request->CDB.CDB32));

			cdb[0] = opcode;
			cdb[1] = flagvals;
			cdb[6] = groupnum;
			cdb[9] = control;

			/* Transfer length */
			cdb[8] = (u8)(num_blocks & 0xff);
			cdb[7] = (u8)((num_blocks >> 8) & 0xff);

			io_request->IoFlags = cpu_to_le16(10); /* Specify 10-byte cdb */
			cdb_len = 10;
		} else if ((cdb_len < 16) && (start_blk > 0xffffffff)) {
			/* Convert to 16 byte CDB for large LBA's */
			switch (cdb_len) {
			case 6:
				opcode = cdb[0] == READ_6 ? READ_16 : WRITE_16;
				control = cdb[5];
				break;
			case 10:
				opcode =
					cdb[0] == READ_10 ? READ_16 : WRITE_16;
				flagvals = cdb[1];
				groupnum = cdb[6];
				control = cdb[9];
				break;
			case 12:
				opcode =
					cdb[0] == READ_12 ? READ_16 : WRITE_16;
				flagvals = cdb[1];
				groupnum = cdb[10];
				control = cdb[11];
				break;
			}

			memset(cdb, 0, sizeof(io_request->CDB.CDB32));

			cdb[0] = opcode;
			cdb[1] = flagvals;
			cdb[14] = groupnum;
			cdb[15] = control;

			/* Transfer length */
			cdb[13] = (u8)(num_blocks & 0xff);
			cdb[12] = (u8)((num_blocks >> 8) & 0xff);
			cdb[11] = (u8)((num_blocks >> 16) & 0xff);
			cdb[10] = (u8)((num_blocks >> 24) & 0xff);

			io_request->IoFlags = cpu_to_le16(16); /* Specify 16-byte cdb */
			cdb_len = 16;
		}

		/* Normal case, just load LBA here */
		switch (cdb_len) {
		case 6:
		{
			u8 val = cdb[1] & 0xE0;
			cdb[3] = (u8)(start_blk & 0xff);
			cdb[2] = (u8)((start_blk >> 8) & 0xff);
			cdb[1] = val | ((u8)(start_blk >> 16) & 0x1f);
			break;
		}
		case 10:
			cdb[5] = (u8)(start_blk & 0xff);
			cdb[4] = (u8)((start_blk >> 8) & 0xff);
			cdb[3] = (u8)((start_blk >> 16) & 0xff);
			cdb[2] = (u8)((start_blk >> 24) & 0xff);
			break;
		case 12:
			cdb[5]    = (u8)(start_blk & 0xff);
			cdb[4]    = (u8)((start_blk >> 8) & 0xff);
			cdb[3]    = (u8)((start_blk >> 16) & 0xff);
			cdb[2]    = (u8)((start_blk >> 24) & 0xff);
			break;
		case 16:
			cdb[9]    = (u8)(start_blk & 0xff);
			cdb[8]    = (u8)((start_blk >> 8) & 0xff);
			cdb[7]    = (u8)((start_blk >> 16) & 0xff);
			cdb[6]    = (u8)((start_blk >> 24) & 0xff);
			cdb[5]    = (u8)((start_blk >> 32) & 0xff);
			cdb[4]    = (u8)((start_blk >> 40) & 0xff);
			cdb[3]    = (u8)((start_blk >> 48) & 0xff);
			cdb[2]    = (u8)((start_blk >> 56) & 0xff);
			break;
		}
	}
}