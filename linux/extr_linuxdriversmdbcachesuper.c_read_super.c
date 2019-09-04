#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct page {int dummy; } ;
struct cache_sb {int offset; int version; int flags; int seq; int first_bucket; int keys; int* d; scalar_t__ csum; int block_size; int data_offset; int nbuckets; int bucket_size; int nr_in_set; int nr_this_dev; int /*<<< orphan*/  last_mount; int /*<<< orphan*/  set_uuid; int /*<<< orphan*/  uuid; int /*<<< orphan*/  magic; int /*<<< orphan*/  label; } ;
struct buffer_head {struct page* b_page; scalar_t__ b_data; } ;
struct block_device {int /*<<< orphan*/  bd_disk; } ;

/* Variables and functions */
#define  BCACHE_SB_VERSION_BDEV 131 
#define  BCACHE_SB_VERSION_BDEV_WITH_OFFSET 130 
#define  BCACHE_SB_VERSION_CDEV 129 
#define  BCACHE_SB_VERSION_CDEV_WITH_UUID 128 
 int BDEV_DATA_START_DEFAULT ; 
 int LONG_MAX ; 
 int MAX_CACHES_PER_SET ; 
 int PAGE_SECTORS ; 
 unsigned int SB_JOURNAL_BUCKETS ; 
 int SB_LABEL_SIZE ; 
 int SB_SECTOR ; 
 int /*<<< orphan*/  SB_SIZE ; 
 struct buffer_head* __bread (struct block_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcache_magic ; 
 scalar_t__ bch_is_zero (int /*<<< orphan*/ ,int) ; 
 int bdev_logical_block_size (struct block_device*) ; 
 scalar_t__ csum_set (struct cache_sb*) ; 
 int get_capacity (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 int /*<<< orphan*/  is_power_of_2 (int) ; 
 scalar_t__ ktime_get_real_seconds () ; 
 void* le16_to_cpu (int) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 void* le64_to_cpu (int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int,int,int) ; 
 int /*<<< orphan*/  put_bh (struct buffer_head*) ; 

__attribute__((used)) static const char *read_super(struct cache_sb *sb, struct block_device *bdev,
			      struct page **res)
{
	const char *err;
	struct cache_sb *s;
	struct buffer_head *bh = __bread(bdev, 1, SB_SIZE);
	unsigned int i;

	if (!bh)
		return "IO error";

	s = (struct cache_sb *) bh->b_data;

	sb->offset		= le64_to_cpu(s->offset);
	sb->version		= le64_to_cpu(s->version);

	memcpy(sb->magic,	s->magic, 16);
	memcpy(sb->uuid,	s->uuid, 16);
	memcpy(sb->set_uuid,	s->set_uuid, 16);
	memcpy(sb->label,	s->label, SB_LABEL_SIZE);

	sb->flags		= le64_to_cpu(s->flags);
	sb->seq			= le64_to_cpu(s->seq);
	sb->last_mount		= le32_to_cpu(s->last_mount);
	sb->first_bucket	= le16_to_cpu(s->first_bucket);
	sb->keys		= le16_to_cpu(s->keys);

	for (i = 0; i < SB_JOURNAL_BUCKETS; i++)
		sb->d[i] = le64_to_cpu(s->d[i]);

	pr_debug("read sb version %llu, flags %llu, seq %llu, journal size %u",
		 sb->version, sb->flags, sb->seq, sb->keys);

	err = "Not a bcache superblock";
	if (sb->offset != SB_SECTOR)
		goto err;

	if (memcmp(sb->magic, bcache_magic, 16))
		goto err;

	err = "Too many journal buckets";
	if (sb->keys > SB_JOURNAL_BUCKETS)
		goto err;

	err = "Bad checksum";
	if (s->csum != csum_set(s))
		goto err;

	err = "Bad UUID";
	if (bch_is_zero(sb->uuid, 16))
		goto err;

	sb->block_size	= le16_to_cpu(s->block_size);

	err = "Superblock block size smaller than device block size";
	if (sb->block_size << 9 < bdev_logical_block_size(bdev))
		goto err;

	switch (sb->version) {
	case BCACHE_SB_VERSION_BDEV:
		sb->data_offset	= BDEV_DATA_START_DEFAULT;
		break;
	case BCACHE_SB_VERSION_BDEV_WITH_OFFSET:
		sb->data_offset	= le64_to_cpu(s->data_offset);

		err = "Bad data offset";
		if (sb->data_offset < BDEV_DATA_START_DEFAULT)
			goto err;

		break;
	case BCACHE_SB_VERSION_CDEV:
	case BCACHE_SB_VERSION_CDEV_WITH_UUID:
		sb->nbuckets	= le64_to_cpu(s->nbuckets);
		sb->bucket_size	= le16_to_cpu(s->bucket_size);

		sb->nr_in_set	= le16_to_cpu(s->nr_in_set);
		sb->nr_this_dev	= le16_to_cpu(s->nr_this_dev);

		err = "Too many buckets";
		if (sb->nbuckets > LONG_MAX)
			goto err;

		err = "Not enough buckets";
		if (sb->nbuckets < 1 << 7)
			goto err;

		err = "Bad block/bucket size";
		if (!is_power_of_2(sb->block_size) ||
		    sb->block_size > PAGE_SECTORS ||
		    !is_power_of_2(sb->bucket_size) ||
		    sb->bucket_size < PAGE_SECTORS)
			goto err;

		err = "Invalid superblock: device too small";
		if (get_capacity(bdev->bd_disk) <
		    sb->bucket_size * sb->nbuckets)
			goto err;

		err = "Bad UUID";
		if (bch_is_zero(sb->set_uuid, 16))
			goto err;

		err = "Bad cache device number in set";
		if (!sb->nr_in_set ||
		    sb->nr_in_set <= sb->nr_this_dev ||
		    sb->nr_in_set > MAX_CACHES_PER_SET)
			goto err;

		err = "Journal buckets not sequential";
		for (i = 0; i < sb->keys; i++)
			if (sb->d[i] != sb->first_bucket + i)
				goto err;

		err = "Too many journal buckets";
		if (sb->first_bucket + sb->keys > sb->nbuckets)
			goto err;

		err = "Invalid superblock: first bucket comes before end of super";
		if (sb->first_bucket * sb->bucket_size < 16)
			goto err;

		break;
	default:
		err = "Unsupported superblock version";
		goto err;
	}

	sb->last_mount = (u32)ktime_get_real_seconds();
	err = NULL;

	get_page(bh->b_page);
	*res = bh->b_page;
err:
	put_bh(bh);
	return err;
}