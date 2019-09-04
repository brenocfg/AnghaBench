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
struct dm_target {int dummy; } ;
struct bio {int /*<<< orphan*/  bi_status; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_NOTSUPP ; 

void dm_remap_zone_report(struct dm_target *ti, struct bio *bio, sector_t start)
{
#ifdef CONFIG_BLK_DEV_ZONED
	struct dm_target_io *tio = container_of(bio, struct dm_target_io, clone);
	struct bio *report_bio = tio->io->orig_bio;
	struct blk_zone_report_hdr *hdr = NULL;
	struct blk_zone *zone;
	unsigned int nr_rep = 0;
	unsigned int ofst;
	sector_t part_offset;
	struct bio_vec bvec;
	struct bvec_iter iter;
	void *addr;

	if (bio->bi_status)
		return;

	/*
	 * bio sector was incremented by the request size on completion. Taking
	 * into account the original request sector, the target start offset on
	 * the backing device and the target mapping offset (ti->begin), the
	 * start sector of the backing device. The partition offset is always 0
	 * if the target uses a whole device.
	 */
	part_offset = bio->bi_iter.bi_sector + ti->begin - (start + bio_end_sector(report_bio));

	/*
	 * Remap the start sector of the reported zones. For sequential zones,
	 * also remap the write pointer position.
	 */
	bio_for_each_segment(bvec, report_bio, iter) {
		addr = kmap_atomic(bvec.bv_page);

		/* Remember the report header in the first page */
		if (!hdr) {
			hdr = addr;
			ofst = sizeof(struct blk_zone_report_hdr);
		} else
			ofst = 0;

		/* Set zones start sector */
		while (hdr->nr_zones && ofst < bvec.bv_len) {
			zone = addr + ofst;
			zone->start -= part_offset;
			if (zone->start >= start + ti->len) {
				hdr->nr_zones = 0;
				break;
			}
			zone->start = zone->start + ti->begin - start;
			if (zone->type != BLK_ZONE_TYPE_CONVENTIONAL) {
				if (zone->cond == BLK_ZONE_COND_FULL)
					zone->wp = zone->start + zone->len;
				else if (zone->cond == BLK_ZONE_COND_EMPTY)
					zone->wp = zone->start;
				else
					zone->wp = zone->wp + ti->begin - start - part_offset;
			}
			ofst += sizeof(struct blk_zone);
			hdr->nr_zones--;
			nr_rep++;
		}

		if (addr != hdr)
			kunmap_atomic(addr);

		if (!hdr->nr_zones)
			break;
	}

	if (hdr) {
		hdr->nr_zones = nr_rep;
		kunmap_atomic(hdr);
	}

	bio_advance(report_bio, report_bio->bi_iter.bi_size);

#else /* !CONFIG_BLK_DEV_ZONED */
	bio->bi_status = BLK_STS_NOTSUPP;
#endif
}