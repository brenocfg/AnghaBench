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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct scsi_cmnd {int* cmnd; } ;
struct raid_map {scalar_t__ parity_rotation_shift; int phys_blk_shift; int /*<<< orphan*/  flags; int /*<<< orphan*/  disk_starting_blk; TYPE_1__* disk_data; int /*<<< orphan*/  row_cnt; int /*<<< orphan*/  metadata_disks_per_row; int /*<<< orphan*/  layout_map_count; int /*<<< orphan*/  strip_size; int /*<<< orphan*/  data_disks_per_row; int /*<<< orphan*/  volume_blk_cnt; } ;
struct pqi_scsi_dev {scalar_t__ raid_level; int offload_to_mirror; struct raid_map* raid_map; } ;
struct pqi_queue_group {int dummy; } ;
struct pqi_encryption_info {int dummy; } ;
struct pqi_ctrl_info {int dummy; } ;
struct TYPE_2__ {scalar_t__ aio_handle; } ;

/* Variables and functions */
 int PQI_RAID_BYPASS_INELIGIBLE ; 
 int RAID_MAP_ENCRYPTION_ENABLED ; 
#define  READ_10 135 
#define  READ_12 134 
#define  READ_16 133 
#define  READ_6 132 
 scalar_t__ SA_RAID_0 ; 
 scalar_t__ SA_RAID_1 ; 
 scalar_t__ SA_RAID_5 ; 
 scalar_t__ SA_RAID_6 ; 
 scalar_t__ SA_RAID_ADM ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
#define  WRITE_10 131 
#define  WRITE_12 130 
#define  WRITE_16 129 
#define  WRITE_6 128 
 scalar_t__ do_div (scalar_t__,scalar_t__) ; 
 scalar_t__ get_unaligned_be16 (int*) ; 
 scalar_t__ get_unaligned_be32 (int*) ; 
 scalar_t__ get_unaligned_be64 (int*) ; 
 int get_unaligned_le16 (int /*<<< orphan*/ *) ; 
 scalar_t__ get_unaligned_le64 (int /*<<< orphan*/ *) ; 
 int pqi_aio_submit_io (struct pqi_ctrl_info*,struct scsi_cmnd*,scalar_t__,int*,int,struct pqi_queue_group*,struct pqi_encryption_info*,int) ; 
 int /*<<< orphan*/  pqi_set_encryption_info (struct pqi_encryption_info*,struct raid_map*,scalar_t__) ; 
 int /*<<< orphan*/  put_unaligned_be16 (scalar_t__,int*) ; 
 int /*<<< orphan*/  put_unaligned_be32 (scalar_t__,int*) ; 
 int /*<<< orphan*/  put_unaligned_be64 (scalar_t__,int*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int pqi_raid_bypass_submit_scsi_cmd(struct pqi_ctrl_info *ctrl_info,
	struct pqi_scsi_dev *device, struct scsi_cmnd *scmd,
	struct pqi_queue_group *queue_group)
{
	struct raid_map *raid_map;
	bool is_write = false;
	u32 map_index;
	u64 first_block;
	u64 last_block;
	u32 block_cnt;
	u32 blocks_per_row;
	u64 first_row;
	u64 last_row;
	u32 first_row_offset;
	u32 last_row_offset;
	u32 first_column;
	u32 last_column;
	u64 r0_first_row;
	u64 r0_last_row;
	u32 r5or6_blocks_per_row;
	u64 r5or6_first_row;
	u64 r5or6_last_row;
	u32 r5or6_first_row_offset;
	u32 r5or6_last_row_offset;
	u32 r5or6_first_column;
	u32 r5or6_last_column;
	u16 data_disks_per_row;
	u32 total_disks_per_row;
	u16 layout_map_count;
	u32 stripesize;
	u16 strip_size;
	u32 first_group;
	u32 last_group;
	u32 current_group;
	u32 map_row;
	u32 aio_handle;
	u64 disk_block;
	u32 disk_block_cnt;
	u8 cdb[16];
	u8 cdb_length;
	int offload_to_mirror;
	struct pqi_encryption_info *encryption_info_ptr;
	struct pqi_encryption_info encryption_info;
#if BITS_PER_LONG == 32
	u64 tmpdiv;
#endif

	/* Check for valid opcode, get LBA and block count. */
	switch (scmd->cmnd[0]) {
	case WRITE_6:
		is_write = true;
		/* fall through */
	case READ_6:
		first_block = (u64)(((scmd->cmnd[1] & 0x1f) << 16) |
			(scmd->cmnd[2] << 8) | scmd->cmnd[3]);
		block_cnt = (u32)scmd->cmnd[4];
		if (block_cnt == 0)
			block_cnt = 256;
		break;
	case WRITE_10:
		is_write = true;
		/* fall through */
	case READ_10:
		first_block = (u64)get_unaligned_be32(&scmd->cmnd[2]);
		block_cnt = (u32)get_unaligned_be16(&scmd->cmnd[7]);
		break;
	case WRITE_12:
		is_write = true;
		/* fall through */
	case READ_12:
		first_block = (u64)get_unaligned_be32(&scmd->cmnd[2]);
		block_cnt = get_unaligned_be32(&scmd->cmnd[6]);
		break;
	case WRITE_16:
		is_write = true;
		/* fall through */
	case READ_16:
		first_block = get_unaligned_be64(&scmd->cmnd[2]);
		block_cnt = get_unaligned_be32(&scmd->cmnd[10]);
		break;
	default:
		/* Process via normal I/O path. */
		return PQI_RAID_BYPASS_INELIGIBLE;
	}

	/* Check for write to non-RAID-0. */
	if (is_write && device->raid_level != SA_RAID_0)
		return PQI_RAID_BYPASS_INELIGIBLE;

	if (unlikely(block_cnt == 0))
		return PQI_RAID_BYPASS_INELIGIBLE;

	last_block = first_block + block_cnt - 1;
	raid_map = device->raid_map;

	/* Check for invalid block or wraparound. */
	if (last_block >= get_unaligned_le64(&raid_map->volume_blk_cnt) ||
		last_block < first_block)
		return PQI_RAID_BYPASS_INELIGIBLE;

	data_disks_per_row = get_unaligned_le16(&raid_map->data_disks_per_row);
	strip_size = get_unaligned_le16(&raid_map->strip_size);
	layout_map_count = get_unaligned_le16(&raid_map->layout_map_count);

	/* Calculate stripe information for the request. */
	blocks_per_row = data_disks_per_row * strip_size;
#if BITS_PER_LONG == 32
	tmpdiv = first_block;
	do_div(tmpdiv, blocks_per_row);
	first_row = tmpdiv;
	tmpdiv = last_block;
	do_div(tmpdiv, blocks_per_row);
	last_row = tmpdiv;
	first_row_offset = (u32)(first_block - (first_row * blocks_per_row));
	last_row_offset = (u32)(last_block - (last_row * blocks_per_row));
	tmpdiv = first_row_offset;
	do_div(tmpdiv, strip_size);
	first_column = tmpdiv;
	tmpdiv = last_row_offset;
	do_div(tmpdiv, strip_size);
	last_column = tmpdiv;
#else
	first_row = first_block / blocks_per_row;
	last_row = last_block / blocks_per_row;
	first_row_offset = (u32)(first_block - (first_row * blocks_per_row));
	last_row_offset = (u32)(last_block - (last_row * blocks_per_row));
	first_column = first_row_offset / strip_size;
	last_column = last_row_offset / strip_size;
#endif

	/* If this isn't a single row/column then give to the controller. */
	if (first_row != last_row || first_column != last_column)
		return PQI_RAID_BYPASS_INELIGIBLE;

	/* Proceeding with driver mapping. */
	total_disks_per_row = data_disks_per_row +
		get_unaligned_le16(&raid_map->metadata_disks_per_row);
	map_row = ((u32)(first_row >> raid_map->parity_rotation_shift)) %
		get_unaligned_le16(&raid_map->row_cnt);
	map_index = (map_row * total_disks_per_row) + first_column;

	/* RAID 1 */
	if (device->raid_level == SA_RAID_1) {
		if (device->offload_to_mirror)
			map_index += data_disks_per_row;
		device->offload_to_mirror = !device->offload_to_mirror;
	} else if (device->raid_level == SA_RAID_ADM) {
		/* RAID ADM */
		/*
		 * Handles N-way mirrors  (R1-ADM) and R10 with # of drives
		 * divisible by 3.
		 */
		offload_to_mirror = device->offload_to_mirror;
		if (offload_to_mirror == 0)  {
			/* use physical disk in the first mirrored group. */
			map_index %= data_disks_per_row;
		} else {
			do {
				/*
				 * Determine mirror group that map_index
				 * indicates.
				 */
				current_group = map_index / data_disks_per_row;

				if (offload_to_mirror != current_group) {
					if (current_group <
						layout_map_count - 1) {
						/*
						 * Select raid index from
						 * next group.
						 */
						map_index += data_disks_per_row;
						current_group++;
					} else {
						/*
						 * Select raid index from first
						 * group.
						 */
						map_index %= data_disks_per_row;
						current_group = 0;
					}
				}
			} while (offload_to_mirror != current_group);
		}

		/* Set mirror group to use next time. */
		offload_to_mirror =
			(offload_to_mirror >= layout_map_count - 1) ?
				0 : offload_to_mirror + 1;
		WARN_ON(offload_to_mirror >= layout_map_count);
		device->offload_to_mirror = offload_to_mirror;
		/*
		 * Avoid direct use of device->offload_to_mirror within this
		 * function since multiple threads might simultaneously
		 * increment it beyond the range of device->layout_map_count -1.
		 */
	} else if ((device->raid_level == SA_RAID_5 ||
		device->raid_level == SA_RAID_6) && layout_map_count > 1) {
		/* RAID 50/60 */
		/* Verify first and last block are in same RAID group */
		r5or6_blocks_per_row = strip_size * data_disks_per_row;
		stripesize = r5or6_blocks_per_row * layout_map_count;
#if BITS_PER_LONG == 32
		tmpdiv = first_block;
		first_group = do_div(tmpdiv, stripesize);
		tmpdiv = first_group;
		do_div(tmpdiv, r5or6_blocks_per_row);
		first_group = tmpdiv;
		tmpdiv = last_block;
		last_group = do_div(tmpdiv, stripesize);
		tmpdiv = last_group;
		do_div(tmpdiv, r5or6_blocks_per_row);
		last_group = tmpdiv;
#else
		first_group = (first_block % stripesize) / r5or6_blocks_per_row;
		last_group = (last_block % stripesize) / r5or6_blocks_per_row;
#endif
		if (first_group != last_group)
			return PQI_RAID_BYPASS_INELIGIBLE;

		/* Verify request is in a single row of RAID 5/6 */
#if BITS_PER_LONG == 32
		tmpdiv = first_block;
		do_div(tmpdiv, stripesize);
		first_row = r5or6_first_row = r0_first_row = tmpdiv;
		tmpdiv = last_block;
		do_div(tmpdiv, stripesize);
		r5or6_last_row = r0_last_row = tmpdiv;
#else
		first_row = r5or6_first_row = r0_first_row =
			first_block / stripesize;
		r5or6_last_row = r0_last_row = last_block / stripesize;
#endif
		if (r5or6_first_row != r5or6_last_row)
			return PQI_RAID_BYPASS_INELIGIBLE;

		/* Verify request is in a single column */
#if BITS_PER_LONG == 32
		tmpdiv = first_block;
		first_row_offset = do_div(tmpdiv, stripesize);
		tmpdiv = first_row_offset;
		first_row_offset = (u32)do_div(tmpdiv, r5or6_blocks_per_row);
		r5or6_first_row_offset = first_row_offset;
		tmpdiv = last_block;
		r5or6_last_row_offset = do_div(tmpdiv, stripesize);
		tmpdiv = r5or6_last_row_offset;
		r5or6_last_row_offset = do_div(tmpdiv, r5or6_blocks_per_row);
		tmpdiv = r5or6_first_row_offset;
		do_div(tmpdiv, strip_size);
		first_column = r5or6_first_column = tmpdiv;
		tmpdiv = r5or6_last_row_offset;
		do_div(tmpdiv, strip_size);
		r5or6_last_column = tmpdiv;
#else
		first_row_offset = r5or6_first_row_offset =
			(u32)((first_block % stripesize) %
			r5or6_blocks_per_row);

		r5or6_last_row_offset =
			(u32)((last_block % stripesize) %
			r5or6_blocks_per_row);

		first_column = r5or6_first_row_offset / strip_size;
		r5or6_first_column = first_column;
		r5or6_last_column = r5or6_last_row_offset / strip_size;
#endif
		if (r5or6_first_column != r5or6_last_column)
			return PQI_RAID_BYPASS_INELIGIBLE;

		/* Request is eligible */
		map_row =
			((u32)(first_row >> raid_map->parity_rotation_shift)) %
			get_unaligned_le16(&raid_map->row_cnt);

		map_index = (first_group *
			(get_unaligned_le16(&raid_map->row_cnt) *
			total_disks_per_row)) +
			(map_row * total_disks_per_row) + first_column;
	}

	aio_handle = raid_map->disk_data[map_index].aio_handle;
	disk_block = get_unaligned_le64(&raid_map->disk_starting_blk) +
		first_row * strip_size +
		(first_row_offset - first_column * strip_size);
	disk_block_cnt = block_cnt;

	/* Handle differing logical/physical block sizes. */
	if (raid_map->phys_blk_shift) {
		disk_block <<= raid_map->phys_blk_shift;
		disk_block_cnt <<= raid_map->phys_blk_shift;
	}

	if (unlikely(disk_block_cnt > 0xffff))
		return PQI_RAID_BYPASS_INELIGIBLE;

	/* Build the new CDB for the physical disk I/O. */
	if (disk_block > 0xffffffff) {
		cdb[0] = is_write ? WRITE_16 : READ_16;
		cdb[1] = 0;
		put_unaligned_be64(disk_block, &cdb[2]);
		put_unaligned_be32(disk_block_cnt, &cdb[10]);
		cdb[14] = 0;
		cdb[15] = 0;
		cdb_length = 16;
	} else {
		cdb[0] = is_write ? WRITE_10 : READ_10;
		cdb[1] = 0;
		put_unaligned_be32((u32)disk_block, &cdb[2]);
		cdb[6] = 0;
		put_unaligned_be16((u16)disk_block_cnt, &cdb[7]);
		cdb[9] = 0;
		cdb_length = 10;
	}

	if (get_unaligned_le16(&raid_map->flags) &
		RAID_MAP_ENCRYPTION_ENABLED) {
		pqi_set_encryption_info(&encryption_info, raid_map,
			first_block);
		encryption_info_ptr = &encryption_info;
	} else {
		encryption_info_ptr = NULL;
	}

	return pqi_aio_submit_io(ctrl_info, scmd, aio_handle,
		cdb, cdb_length, queue_group, encryption_info_ptr, true);
}