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
typedef  int u8 ;
typedef  int u64 ;
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct scsi_cmnd {int* cmnd; TYPE_1__* device; } ;
struct raid_map_disk_data {scalar_t__ ioaccel_handle; } ;
struct raid_map_data {scalar_t__ data_disks_per_row; scalar_t__ strip_size; scalar_t__ metadata_disks_per_row; int parity_rotation_shift; scalar_t__ row_cnt; scalar_t__ layout_map_count; int phys_blk_shift; int /*<<< orphan*/  disk_starting_blk; int /*<<< orphan*/  volume_blk_cnt; struct raid_map_disk_data* data; } ;
struct hpsa_scsi_dev_t {int raid_level; int offload_to_mirror; int /*<<< orphan*/ * phys_disk; int /*<<< orphan*/  scsi3addr; scalar_t__ in_reset; struct raid_map_data raid_map; } ;
struct ctlr_info {int dummy; } ;
struct CommandList {int /*<<< orphan*/  phys_disk; struct scsi_cmnd* scsi_cmd; } ;
struct TYPE_2__ {struct hpsa_scsi_dev_t* hostdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
#define  HPSA_RAID_0 140 
#define  HPSA_RAID_1 139 
#define  HPSA_RAID_5 138 
#define  HPSA_RAID_6 137 
#define  HPSA_RAID_ADM 136 
 int IO_ACCEL_INELIGIBLE ; 
 scalar_t__ RAID_MAP_MAX_ENTRIES ; 
#define  READ_10 135 
#define  READ_12 134 
#define  READ_16 133 
#define  READ_6 132 
#define  WRITE_10 131 
#define  WRITE_12 130 
#define  WRITE_16 129 
#define  WRITE_6 128 
 scalar_t__ do_div (int,scalar_t__) ; 
 int hpsa_scsi_ioaccel_queue_command (struct ctlr_info*,struct CommandList*,scalar_t__,int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ le16_to_cpu (scalar_t__) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raid_map_helper (struct raid_map_data*,int,scalar_t__*,scalar_t__*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int hpsa_scsi_ioaccel_raid_map(struct ctlr_info *h,
	struct CommandList *c)
{
	struct scsi_cmnd *cmd = c->scsi_cmd;
	struct hpsa_scsi_dev_t *dev = cmd->device->hostdata;
	struct raid_map_data *map = &dev->raid_map;
	struct raid_map_disk_data *dd = &map->data[0];
	int is_write = 0;
	u32 map_index;
	u64 first_block, last_block;
	u32 block_cnt;
	u32 blocks_per_row;
	u64 first_row, last_row;
	u32 first_row_offset, last_row_offset;
	u32 first_column, last_column;
	u64 r0_first_row, r0_last_row;
	u32 r5or6_blocks_per_row;
	u64 r5or6_first_row, r5or6_last_row;
	u32 r5or6_first_row_offset, r5or6_last_row_offset;
	u32 r5or6_first_column, r5or6_last_column;
	u32 total_disks_per_row;
	u32 stripesize;
	u32 first_group, last_group, current_group;
	u32 map_row;
	u32 disk_handle;
	u64 disk_block;
	u32 disk_block_cnt;
	u8 cdb[16];
	u8 cdb_len;
	u16 strip_size;
#if BITS_PER_LONG == 32
	u64 tmpdiv;
#endif
	int offload_to_mirror;

	if (!dev)
		return -1;

	if (dev->in_reset)
		return -1;

	/* check for valid opcode, get LBA and block count */
	switch (cmd->cmnd[0]) {
	case WRITE_6:
		is_write = 1;
		/* fall through */
	case READ_6:
		first_block = (((cmd->cmnd[1] & 0x1F) << 16) |
				(cmd->cmnd[2] << 8) |
				cmd->cmnd[3]);
		block_cnt = cmd->cmnd[4];
		if (block_cnt == 0)
			block_cnt = 256;
		break;
	case WRITE_10:
		is_write = 1;
		/* fall through */
	case READ_10:
		first_block =
			(((u64) cmd->cmnd[2]) << 24) |
			(((u64) cmd->cmnd[3]) << 16) |
			(((u64) cmd->cmnd[4]) << 8) |
			cmd->cmnd[5];
		block_cnt =
			(((u32) cmd->cmnd[7]) << 8) |
			cmd->cmnd[8];
		break;
	case WRITE_12:
		is_write = 1;
		/* fall through */
	case READ_12:
		first_block =
			(((u64) cmd->cmnd[2]) << 24) |
			(((u64) cmd->cmnd[3]) << 16) |
			(((u64) cmd->cmnd[4]) << 8) |
			cmd->cmnd[5];
		block_cnt =
			(((u32) cmd->cmnd[6]) << 24) |
			(((u32) cmd->cmnd[7]) << 16) |
			(((u32) cmd->cmnd[8]) << 8) |
		cmd->cmnd[9];
		break;
	case WRITE_16:
		is_write = 1;
		/* fall through */
	case READ_16:
		first_block =
			(((u64) cmd->cmnd[2]) << 56) |
			(((u64) cmd->cmnd[3]) << 48) |
			(((u64) cmd->cmnd[4]) << 40) |
			(((u64) cmd->cmnd[5]) << 32) |
			(((u64) cmd->cmnd[6]) << 24) |
			(((u64) cmd->cmnd[7]) << 16) |
			(((u64) cmd->cmnd[8]) << 8) |
			cmd->cmnd[9];
		block_cnt =
			(((u32) cmd->cmnd[10]) << 24) |
			(((u32) cmd->cmnd[11]) << 16) |
			(((u32) cmd->cmnd[12]) << 8) |
			cmd->cmnd[13];
		break;
	default:
		return IO_ACCEL_INELIGIBLE; /* process via normal I/O path */
	}
	last_block = first_block + block_cnt - 1;

	/* check for write to non-RAID-0 */
	if (is_write && dev->raid_level != 0)
		return IO_ACCEL_INELIGIBLE;

	/* check for invalid block or wraparound */
	if (last_block >= le64_to_cpu(map->volume_blk_cnt) ||
		last_block < first_block)
		return IO_ACCEL_INELIGIBLE;

	/* calculate stripe information for the request */
	blocks_per_row = le16_to_cpu(map->data_disks_per_row) *
				le16_to_cpu(map->strip_size);
	strip_size = le16_to_cpu(map->strip_size);
#if BITS_PER_LONG == 32
	tmpdiv = first_block;
	(void) do_div(tmpdiv, blocks_per_row);
	first_row = tmpdiv;
	tmpdiv = last_block;
	(void) do_div(tmpdiv, blocks_per_row);
	last_row = tmpdiv;
	first_row_offset = (u32) (first_block - (first_row * blocks_per_row));
	last_row_offset = (u32) (last_block - (last_row * blocks_per_row));
	tmpdiv = first_row_offset;
	(void) do_div(tmpdiv, strip_size);
	first_column = tmpdiv;
	tmpdiv = last_row_offset;
	(void) do_div(tmpdiv, strip_size);
	last_column = tmpdiv;
#else
	first_row = first_block / blocks_per_row;
	last_row = last_block / blocks_per_row;
	first_row_offset = (u32) (first_block - (first_row * blocks_per_row));
	last_row_offset = (u32) (last_block - (last_row * blocks_per_row));
	first_column = first_row_offset / strip_size;
	last_column = last_row_offset / strip_size;
#endif

	/* if this isn't a single row/column then give to the controller */
	if ((first_row != last_row) || (first_column != last_column))
		return IO_ACCEL_INELIGIBLE;

	/* proceeding with driver mapping */
	total_disks_per_row = le16_to_cpu(map->data_disks_per_row) +
				le16_to_cpu(map->metadata_disks_per_row);
	map_row = ((u32)(first_row >> map->parity_rotation_shift)) %
				le16_to_cpu(map->row_cnt);
	map_index = (map_row * total_disks_per_row) + first_column;

	switch (dev->raid_level) {
	case HPSA_RAID_0:
		break; /* nothing special to do */
	case HPSA_RAID_1:
		/* Handles load balance across RAID 1 members.
		 * (2-drive R1 and R10 with even # of drives.)
		 * Appropriate for SSDs, not optimal for HDDs
		 */
		BUG_ON(le16_to_cpu(map->layout_map_count) != 2);
		if (dev->offload_to_mirror)
			map_index += le16_to_cpu(map->data_disks_per_row);
		dev->offload_to_mirror = !dev->offload_to_mirror;
		break;
	case HPSA_RAID_ADM:
		/* Handles N-way mirrors  (R1-ADM)
		 * and R10 with # of drives divisible by 3.)
		 */
		BUG_ON(le16_to_cpu(map->layout_map_count) != 3);

		offload_to_mirror = dev->offload_to_mirror;
		raid_map_helper(map, offload_to_mirror,
				&map_index, &current_group);
		/* set mirror group to use next time */
		offload_to_mirror =
			(offload_to_mirror >=
			le16_to_cpu(map->layout_map_count) - 1)
			? 0 : offload_to_mirror + 1;
		dev->offload_to_mirror = offload_to_mirror;
		/* Avoid direct use of dev->offload_to_mirror within this
		 * function since multiple threads might simultaneously
		 * increment it beyond the range of dev->layout_map_count -1.
		 */
		break;
	case HPSA_RAID_5:
	case HPSA_RAID_6:
		if (le16_to_cpu(map->layout_map_count) <= 1)
			break;

		/* Verify first and last block are in same RAID group */
		r5or6_blocks_per_row =
			le16_to_cpu(map->strip_size) *
			le16_to_cpu(map->data_disks_per_row);
		BUG_ON(r5or6_blocks_per_row == 0);
		stripesize = r5or6_blocks_per_row *
			le16_to_cpu(map->layout_map_count);
#if BITS_PER_LONG == 32
		tmpdiv = first_block;
		first_group = do_div(tmpdiv, stripesize);
		tmpdiv = first_group;
		(void) do_div(tmpdiv, r5or6_blocks_per_row);
		first_group = tmpdiv;
		tmpdiv = last_block;
		last_group = do_div(tmpdiv, stripesize);
		tmpdiv = last_group;
		(void) do_div(tmpdiv, r5or6_blocks_per_row);
		last_group = tmpdiv;
#else
		first_group = (first_block % stripesize) / r5or6_blocks_per_row;
		last_group = (last_block % stripesize) / r5or6_blocks_per_row;
#endif
		if (first_group != last_group)
			return IO_ACCEL_INELIGIBLE;

		/* Verify request is in a single row of RAID 5/6 */
#if BITS_PER_LONG == 32
		tmpdiv = first_block;
		(void) do_div(tmpdiv, stripesize);
		first_row = r5or6_first_row = r0_first_row = tmpdiv;
		tmpdiv = last_block;
		(void) do_div(tmpdiv, stripesize);
		r5or6_last_row = r0_last_row = tmpdiv;
#else
		first_row = r5or6_first_row = r0_first_row =
						first_block / stripesize;
		r5or6_last_row = r0_last_row = last_block / stripesize;
#endif
		if (r5or6_first_row != r5or6_last_row)
			return IO_ACCEL_INELIGIBLE;


		/* Verify request is in a single column */
#if BITS_PER_LONG == 32
		tmpdiv = first_block;
		first_row_offset = do_div(tmpdiv, stripesize);
		tmpdiv = first_row_offset;
		first_row_offset = (u32) do_div(tmpdiv, r5or6_blocks_per_row);
		r5or6_first_row_offset = first_row_offset;
		tmpdiv = last_block;
		r5or6_last_row_offset = do_div(tmpdiv, stripesize);
		tmpdiv = r5or6_last_row_offset;
		r5or6_last_row_offset = do_div(tmpdiv, r5or6_blocks_per_row);
		tmpdiv = r5or6_first_row_offset;
		(void) do_div(tmpdiv, map->strip_size);
		first_column = r5or6_first_column = tmpdiv;
		tmpdiv = r5or6_last_row_offset;
		(void) do_div(tmpdiv, map->strip_size);
		r5or6_last_column = tmpdiv;
#else
		first_row_offset = r5or6_first_row_offset =
			(u32)((first_block % stripesize) %
						r5or6_blocks_per_row);

		r5or6_last_row_offset =
			(u32)((last_block % stripesize) %
						r5or6_blocks_per_row);

		first_column = r5or6_first_column =
			r5or6_first_row_offset / le16_to_cpu(map->strip_size);
		r5or6_last_column =
			r5or6_last_row_offset / le16_to_cpu(map->strip_size);
#endif
		if (r5or6_first_column != r5or6_last_column)
			return IO_ACCEL_INELIGIBLE;

		/* Request is eligible */
		map_row = ((u32)(first_row >> map->parity_rotation_shift)) %
			le16_to_cpu(map->row_cnt);

		map_index = (first_group *
			(le16_to_cpu(map->row_cnt) * total_disks_per_row)) +
			(map_row * total_disks_per_row) + first_column;
		break;
	default:
		return IO_ACCEL_INELIGIBLE;
	}

	if (unlikely(map_index >= RAID_MAP_MAX_ENTRIES))
		return IO_ACCEL_INELIGIBLE;

	c->phys_disk = dev->phys_disk[map_index];
	if (!c->phys_disk)
		return IO_ACCEL_INELIGIBLE;

	disk_handle = dd[map_index].ioaccel_handle;
	disk_block = le64_to_cpu(map->disk_starting_blk) +
			first_row * le16_to_cpu(map->strip_size) +
			(first_row_offset - first_column *
			le16_to_cpu(map->strip_size));
	disk_block_cnt = block_cnt;

	/* handle differing logical/physical block sizes */
	if (map->phys_blk_shift) {
		disk_block <<= map->phys_blk_shift;
		disk_block_cnt <<= map->phys_blk_shift;
	}
	BUG_ON(disk_block_cnt > 0xffff);

	/* build the new CDB for the physical disk I/O */
	if (disk_block > 0xffffffff) {
		cdb[0] = is_write ? WRITE_16 : READ_16;
		cdb[1] = 0;
		cdb[2] = (u8) (disk_block >> 56);
		cdb[3] = (u8) (disk_block >> 48);
		cdb[4] = (u8) (disk_block >> 40);
		cdb[5] = (u8) (disk_block >> 32);
		cdb[6] = (u8) (disk_block >> 24);
		cdb[7] = (u8) (disk_block >> 16);
		cdb[8] = (u8) (disk_block >> 8);
		cdb[9] = (u8) (disk_block);
		cdb[10] = (u8) (disk_block_cnt >> 24);
		cdb[11] = (u8) (disk_block_cnt >> 16);
		cdb[12] = (u8) (disk_block_cnt >> 8);
		cdb[13] = (u8) (disk_block_cnt);
		cdb[14] = 0;
		cdb[15] = 0;
		cdb_len = 16;
	} else {
		cdb[0] = is_write ? WRITE_10 : READ_10;
		cdb[1] = 0;
		cdb[2] = (u8) (disk_block >> 24);
		cdb[3] = (u8) (disk_block >> 16);
		cdb[4] = (u8) (disk_block >> 8);
		cdb[5] = (u8) (disk_block);
		cdb[6] = 0;
		cdb[7] = (u8) (disk_block_cnt >> 8);
		cdb[8] = (u8) (disk_block_cnt);
		cdb[9] = 0;
		cdb_len = 10;
	}
	return hpsa_scsi_ioaccel_queue_command(h, c, disk_handle, cdb, cdb_len,
						dev->scsi3addr,
						dev->phys_disk[map_index]);
}