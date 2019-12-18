#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct TYPE_6__ {int /*<<< orphan*/  size; int /*<<< orphan*/  offset; } ;
struct mdp_superblock_1 {scalar_t__ magic; scalar_t__ major_version; scalar_t__ max_dev; scalar_t__ feature_map; scalar_t__ sb_csum; scalar_t__ new_offset; scalar_t__ cnt_corrected_read; scalar_t__ level; scalar_t__ dev_number; scalar_t__ bblog_offset; int bblog_shift; scalar_t__ layout; scalar_t__ chunksize; int /*<<< orphan*/  data_size; int /*<<< orphan*/  events; scalar_t__* set_uuid; TYPE_1__ ppl; int /*<<< orphan*/  bblog_size; int /*<<< orphan*/  data_offset; scalar_t__* pad3; scalar_t__ pad0; int /*<<< orphan*/  super_offset; } ;
struct TYPE_7__ {scalar_t__ offset; scalar_t__ sector; void* size; } ;
struct TYPE_10__ {scalar_t__ count; int shift; } ;
struct md_rdev {int sb_start; int preferred_minor; int data_offset; int new_data_offset; int sb_size; int desc_nr; int sectors; TYPE_4__* bdev; scalar_t__ sb_page; TYPE_2__ ppl; TYPE_5__ badblocks; scalar_t__ bb_page; int /*<<< orphan*/  corrected_errors; } ;
typedef  int sector_t ;
typedef  int s32 ;
typedef  int __u64 ;
typedef  scalar_t__ __s16 ;
typedef  int /*<<< orphan*/  __le64 ;
struct TYPE_9__ {int /*<<< orphan*/  bd_inode; TYPE_3__* bd_disk; } ;
struct TYPE_8__ {int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int BDEVNAME_SIZE ; 
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int LEVEL_MULTIPATH ; 
 int MD_FEATURE_ALL ; 
 int MD_FEATURE_BAD_BLOCKS ; 
 int MD_FEATURE_MULTIPLE_PPLS ; 
 int MD_FEATURE_NEW_OFFSET ; 
 int MD_FEATURE_PPL ; 
 int MD_FEATURE_RAID0_LAYOUT ; 
 int MD_FEATURE_RESHAPE_ACTIVE ; 
 int MD_SB_MAGIC ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  REQ_OP_READ ; 
 scalar_t__ alloc_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 scalar_t__ badblocks_set (TYPE_5__*,int,int,int) ; 
 int /*<<< orphan*/  bdevname (TYPE_4__*,char*) ; 
 scalar_t__ calc_sb_1_csum (struct mdp_superblock_1*) ; 
 scalar_t__ cpu_to_le32 (int) ; 
 int i_size_read (int /*<<< orphan*/ ) ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (scalar_t__) ; 
 int le64_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (scalar_t__*,scalar_t__*,int) ; 
 struct mdp_superblock_1* page_address (scalar_t__) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,...) ; 
 int queue_logical_block_size (int /*<<< orphan*/ ) ; 
 int read_disk_sb (struct md_rdev*,int) ; 
 int /*<<< orphan*/  sync_page_io (struct md_rdev*,int,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int super_1_load(struct md_rdev *rdev, struct md_rdev *refdev, int minor_version)
{
	struct mdp_superblock_1 *sb;
	int ret;
	sector_t sb_start;
	sector_t sectors;
	char b[BDEVNAME_SIZE], b2[BDEVNAME_SIZE];
	int bmask;

	/*
	 * Calculate the position of the superblock in 512byte sectors.
	 * It is always aligned to a 4K boundary and
	 * depeding on minor_version, it can be:
	 * 0: At least 8K, but less than 12K, from end of device
	 * 1: At start of device
	 * 2: 4K from start of device.
	 */
	switch(minor_version) {
	case 0:
		sb_start = i_size_read(rdev->bdev->bd_inode) >> 9;
		sb_start -= 8*2;
		sb_start &= ~(sector_t)(4*2-1);
		break;
	case 1:
		sb_start = 0;
		break;
	case 2:
		sb_start = 8;
		break;
	default:
		return -EINVAL;
	}
	rdev->sb_start = sb_start;

	/* superblock is rarely larger than 1K, but it can be larger,
	 * and it is safe to read 4k, so we do that
	 */
	ret = read_disk_sb(rdev, 4096);
	if (ret) return ret;

	sb = page_address(rdev->sb_page);

	if (sb->magic != cpu_to_le32(MD_SB_MAGIC) ||
	    sb->major_version != cpu_to_le32(1) ||
	    le32_to_cpu(sb->max_dev) > (4096-256)/2 ||
	    le64_to_cpu(sb->super_offset) != rdev->sb_start ||
	    (le32_to_cpu(sb->feature_map) & ~MD_FEATURE_ALL) != 0)
		return -EINVAL;

	if (calc_sb_1_csum(sb) != sb->sb_csum) {
		pr_warn("md: invalid superblock checksum on %s\n",
			bdevname(rdev->bdev,b));
		return -EINVAL;
	}
	if (le64_to_cpu(sb->data_size) < 10) {
		pr_warn("md: data_size too small on %s\n",
			bdevname(rdev->bdev,b));
		return -EINVAL;
	}
	if (sb->pad0 ||
	    sb->pad3[0] ||
	    memcmp(sb->pad3, sb->pad3+1, sizeof(sb->pad3) - sizeof(sb->pad3[1])))
		/* Some padding is non-zero, might be a new feature */
		return -EINVAL;

	rdev->preferred_minor = 0xffff;
	rdev->data_offset = le64_to_cpu(sb->data_offset);
	rdev->new_data_offset = rdev->data_offset;
	if ((le32_to_cpu(sb->feature_map) & MD_FEATURE_RESHAPE_ACTIVE) &&
	    (le32_to_cpu(sb->feature_map) & MD_FEATURE_NEW_OFFSET))
		rdev->new_data_offset += (s32)le32_to_cpu(sb->new_offset);
	atomic_set(&rdev->corrected_errors, le32_to_cpu(sb->cnt_corrected_read));

	rdev->sb_size = le32_to_cpu(sb->max_dev) * 2 + 256;
	bmask = queue_logical_block_size(rdev->bdev->bd_disk->queue)-1;
	if (rdev->sb_size & bmask)
		rdev->sb_size = (rdev->sb_size | bmask) + 1;

	if (minor_version
	    && rdev->data_offset < sb_start + (rdev->sb_size/512))
		return -EINVAL;
	if (minor_version
	    && rdev->new_data_offset < sb_start + (rdev->sb_size/512))
		return -EINVAL;

	if (sb->level == cpu_to_le32(LEVEL_MULTIPATH))
		rdev->desc_nr = -1;
	else
		rdev->desc_nr = le32_to_cpu(sb->dev_number);

	if (!rdev->bb_page) {
		rdev->bb_page = alloc_page(GFP_KERNEL);
		if (!rdev->bb_page)
			return -ENOMEM;
	}
	if ((le32_to_cpu(sb->feature_map) & MD_FEATURE_BAD_BLOCKS) &&
	    rdev->badblocks.count == 0) {
		/* need to load the bad block list.
		 * Currently we limit it to one page.
		 */
		s32 offset;
		sector_t bb_sector;
		__le64 *bbp;
		int i;
		int sectors = le16_to_cpu(sb->bblog_size);
		if (sectors > (PAGE_SIZE / 512))
			return -EINVAL;
		offset = le32_to_cpu(sb->bblog_offset);
		if (offset == 0)
			return -EINVAL;
		bb_sector = (long long)offset;
		if (!sync_page_io(rdev, bb_sector, sectors << 9,
				  rdev->bb_page, REQ_OP_READ, 0, true))
			return -EIO;
		bbp = (__le64 *)page_address(rdev->bb_page);
		rdev->badblocks.shift = sb->bblog_shift;
		for (i = 0 ; i < (sectors << (9-3)) ; i++, bbp++) {
			u64 bb = le64_to_cpu(*bbp);
			int count = bb & (0x3ff);
			u64 sector = bb >> 10;
			sector <<= sb->bblog_shift;
			count <<= sb->bblog_shift;
			if (bb + 1 == 0)
				break;
			if (badblocks_set(&rdev->badblocks, sector, count, 1))
				return -EINVAL;
		}
	} else if (sb->bblog_offset != 0)
		rdev->badblocks.shift = 0;

	if ((le32_to_cpu(sb->feature_map) &
	    (MD_FEATURE_PPL | MD_FEATURE_MULTIPLE_PPLS))) {
		rdev->ppl.offset = (__s16)le16_to_cpu(sb->ppl.offset);
		rdev->ppl.size = le16_to_cpu(sb->ppl.size);
		rdev->ppl.sector = rdev->sb_start + rdev->ppl.offset;
	}

	if ((le32_to_cpu(sb->feature_map) & MD_FEATURE_RAID0_LAYOUT) &&
	    sb->level != 0)
		return -EINVAL;

	if (!refdev) {
		ret = 1;
	} else {
		__u64 ev1, ev2;
		struct mdp_superblock_1 *refsb = page_address(refdev->sb_page);

		if (memcmp(sb->set_uuid, refsb->set_uuid, 16) != 0 ||
		    sb->level != refsb->level ||
		    sb->layout != refsb->layout ||
		    sb->chunksize != refsb->chunksize) {
			pr_warn("md: %s has strangely different superblock to %s\n",
				bdevname(rdev->bdev,b),
				bdevname(refdev->bdev,b2));
			return -EINVAL;
		}
		ev1 = le64_to_cpu(sb->events);
		ev2 = le64_to_cpu(refsb->events);

		if (ev1 > ev2)
			ret = 1;
		else
			ret = 0;
	}
	if (minor_version) {
		sectors = (i_size_read(rdev->bdev->bd_inode) >> 9);
		sectors -= rdev->data_offset;
	} else
		sectors = rdev->sb_start;
	if (sectors < le64_to_cpu(sb->data_size))
		return -EINVAL;
	rdev->sectors = le64_to_cpu(sb->data_size);
	return ret;
}