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
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
struct dmz_super {scalar_t__ nr_bitmap_blocks; scalar_t__ nr_map_blocks; scalar_t__ nr_chunks; scalar_t__ nr_reserved_seq; scalar_t__ nr_meta_blocks; scalar_t__ version; scalar_t__ magic; scalar_t__ crc; int /*<<< orphan*/  gen; } ;
struct dmz_metadata {unsigned int nr_rnd_zones; unsigned int nr_useable_zones; unsigned int nr_meta_blocks; unsigned int nr_reserved_seq; unsigned int nr_chunks; unsigned int nr_map_blocks; unsigned int nr_bitmap_blocks; unsigned int nr_meta_zones; unsigned int nr_data_zones; struct dmz_dev* dev; } ;
struct dmz_dev {int zone_nr_blocks; int zone_nr_blocks_shift; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMZ_BLOCK_SIZE ; 
 unsigned int DMZ_MAGIC ; 
 unsigned int DMZ_META_VER ; 
 int ENXIO ; 
 scalar_t__ crc32_le (int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmz_dev_err (struct dmz_dev*,char*,...) ; 
 unsigned int le32_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dmz_check_sb(struct dmz_metadata *zmd, struct dmz_super *sb)
{
	unsigned int nr_meta_zones, nr_data_zones;
	struct dmz_dev *dev = zmd->dev;
	u32 crc, stored_crc;
	u64 gen;

	gen = le64_to_cpu(sb->gen);
	stored_crc = le32_to_cpu(sb->crc);
	sb->crc = 0;
	crc = crc32_le(gen, (unsigned char *)sb, DMZ_BLOCK_SIZE);
	if (crc != stored_crc) {
		dmz_dev_err(dev, "Invalid checksum (needed 0x%08x, got 0x%08x)",
			    crc, stored_crc);
		return -ENXIO;
	}

	if (le32_to_cpu(sb->magic) != DMZ_MAGIC) {
		dmz_dev_err(dev, "Invalid meta magic (needed 0x%08x, got 0x%08x)",
			    DMZ_MAGIC, le32_to_cpu(sb->magic));
		return -ENXIO;
	}

	if (le32_to_cpu(sb->version) != DMZ_META_VER) {
		dmz_dev_err(dev, "Invalid meta version (needed %d, got %d)",
			    DMZ_META_VER, le32_to_cpu(sb->version));
		return -ENXIO;
	}

	nr_meta_zones = (le32_to_cpu(sb->nr_meta_blocks) + dev->zone_nr_blocks - 1)
		>> dev->zone_nr_blocks_shift;
	if (!nr_meta_zones ||
	    nr_meta_zones >= zmd->nr_rnd_zones) {
		dmz_dev_err(dev, "Invalid number of metadata blocks");
		return -ENXIO;
	}

	if (!le32_to_cpu(sb->nr_reserved_seq) ||
	    le32_to_cpu(sb->nr_reserved_seq) >= (zmd->nr_useable_zones - nr_meta_zones)) {
		dmz_dev_err(dev, "Invalid number of reserved sequential zones");
		return -ENXIO;
	}

	nr_data_zones = zmd->nr_useable_zones -
		(nr_meta_zones * 2 + le32_to_cpu(sb->nr_reserved_seq));
	if (le32_to_cpu(sb->nr_chunks) > nr_data_zones) {
		dmz_dev_err(dev, "Invalid number of chunks %u / %u",
			    le32_to_cpu(sb->nr_chunks), nr_data_zones);
		return -ENXIO;
	}

	/* OK */
	zmd->nr_meta_blocks = le32_to_cpu(sb->nr_meta_blocks);
	zmd->nr_reserved_seq = le32_to_cpu(sb->nr_reserved_seq);
	zmd->nr_chunks = le32_to_cpu(sb->nr_chunks);
	zmd->nr_map_blocks = le32_to_cpu(sb->nr_map_blocks);
	zmd->nr_bitmap_blocks = le32_to_cpu(sb->nr_bitmap_blocks);
	zmd->nr_meta_zones = nr_meta_zones;
	zmd->nr_data_zones = nr_data_zones;

	return 0;
}