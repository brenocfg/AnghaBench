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
struct request {int dummy; } ;
struct dasd_device {int default_expires; int /*<<< orphan*/  default_retries; } ;
struct dasd_ccw_req {int expires; int /*<<< orphan*/  status; int /*<<< orphan*/  buildclk; int /*<<< orphan*/  retries; struct dasd_block* block; struct dasd_device* memdev; struct dasd_device* startdev; int /*<<< orphan*/  flags; struct LO_fba_data* data; struct ccw1* cpaddr; } ;
struct dasd_block {unsigned int bp_block; int s2b_shift; TYPE_1__* base; } ;
struct ccw1 {int /*<<< orphan*/  flags; } ;
struct LO_fba_data {int dummy; } ;
struct DE_fba_data {int dummy; } ;
typedef  int sector_t ;
struct TYPE_2__ {int features; } ;

/* Variables and functions */
 unsigned int BLOCKS_PER_PAGE (unsigned int) ; 
 int /*<<< orphan*/  CCW_FLAG_CC ; 
 int /*<<< orphan*/  DASD_CQR_FILLED ; 
 int /*<<< orphan*/  DASD_CQR_FLAGS_FAILFAST ; 
 int /*<<< orphan*/  DASD_FBA_MAGIC ; 
 int DASD_FEATURE_FAILFAST ; 
 int HZ ; 
 scalar_t__ IS_ERR (struct dasd_ccw_req*) ; 
 int /*<<< orphan*/  WRITE ; 
 int /*<<< orphan*/  blk_mq_rq_to_pdu (struct request*) ; 
 scalar_t__ blk_noretry_request (struct request*) ; 
 int blk_rq_pos (struct request*) ; 
 int blk_rq_sectors (struct request*) ; 
 int /*<<< orphan*/  ccw_write_no_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccw_write_zero (int /*<<< orphan*/ ,int) ; 
 int count_ccws (int,int,unsigned int) ; 
 struct dasd_ccw_req* dasd_smalloc_request (int /*<<< orphan*/ ,int,int,struct dasd_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  define_extent (int /*<<< orphan*/ ,struct LO_fba_data*,int /*<<< orphan*/ ,unsigned int,int,int) ; 
 int /*<<< orphan*/  get_tod_clock () ; 
 int /*<<< orphan*/  locate_record (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct dasd_ccw_req *dasd_fba_build_cp_discard(
						struct dasd_device *memdev,
						struct dasd_block *block,
						struct request *req)
{
	struct LO_fba_data *LO_data;
	struct dasd_ccw_req *cqr;
	struct ccw1 *ccw;

	sector_t wz_stop = 0, d_stop = 0;
	sector_t first_rec, last_rec;

	unsigned int blksize = block->bp_block;
	unsigned int blocks_per_page;
	int wz_count = 0;
	int d_count = 0;
	int cur_pos = 0; /* Current position within the extent */
	int count = 0;
	int cplength;
	int datasize;
	int nr_ccws;

	first_rec = blk_rq_pos(req) >> block->s2b_shift;
	last_rec =
		(blk_rq_pos(req) + blk_rq_sectors(req) - 1) >> block->s2b_shift;
	count = last_rec - first_rec + 1;

	blocks_per_page = BLOCKS_PER_PAGE(blksize);
	nr_ccws = count_ccws(first_rec, last_rec, blocks_per_page);

	/* define extent + nr_ccws * locate record + nr_ccws * single CCW */
	cplength = 1 + 2 * nr_ccws;
	datasize = sizeof(struct DE_fba_data) +
		nr_ccws * (sizeof(struct LO_fba_data) + sizeof(struct ccw1));

	cqr = dasd_smalloc_request(DASD_FBA_MAGIC, cplength, datasize, memdev,
				   blk_mq_rq_to_pdu(req));
	if (IS_ERR(cqr))
		return cqr;

	ccw = cqr->cpaddr;

	define_extent(ccw++, cqr->data, WRITE, blksize, first_rec, count);
	LO_data = cqr->data + sizeof(struct DE_fba_data);

	/* First part is not aligned. Calculate range to write zeroes. */
	if (first_rec % blocks_per_page != 0) {
		wz_stop = first_rec + blocks_per_page -
			(first_rec % blocks_per_page) - 1;
		if (wz_stop > last_rec)
			wz_stop = last_rec;
		wz_count = wz_stop - first_rec + 1;

		ccw[-1].flags |= CCW_FLAG_CC;
		locate_record(ccw++, LO_data++, WRITE, cur_pos, wz_count);

		ccw[-1].flags |= CCW_FLAG_CC;
		ccw_write_zero(ccw++, wz_count * blksize);

		cur_pos = wz_count;
	}

	/* We can do proper discard when we've got at least blocks_per_page blocks. */
	if (last_rec - (first_rec + cur_pos) + 1 >= blocks_per_page) {
		/* is last record at page boundary? */
		if ((last_rec - blocks_per_page + 1) % blocks_per_page != 0)
			d_stop = last_rec - ((last_rec - blocks_per_page + 1) %
					     blocks_per_page);
		else
			d_stop = last_rec;

		d_count = d_stop - (first_rec + cur_pos) + 1;

		ccw[-1].flags |= CCW_FLAG_CC;
		locate_record(ccw++, LO_data++, WRITE, cur_pos, d_count);

		ccw[-1].flags |= CCW_FLAG_CC;
		ccw_write_no_data(ccw++);

		cur_pos += d_count;
	}

	/* We might still have some bits left which need to be zeroed. */
	if (cur_pos == 0 || first_rec + cur_pos - 1 < last_rec) {
		if (d_stop != 0)
			wz_count = last_rec - d_stop;
		else if (wz_stop != 0)
			wz_count = last_rec - wz_stop;
		else
			wz_count = count;

		ccw[-1].flags |= CCW_FLAG_CC;
		locate_record(ccw++, LO_data++, WRITE, cur_pos, wz_count);

		ccw[-1].flags |= CCW_FLAG_CC;
		ccw_write_zero(ccw++, wz_count * blksize);
	}

	if (blk_noretry_request(req) ||
	    block->base->features & DASD_FEATURE_FAILFAST)
		set_bit(DASD_CQR_FLAGS_FAILFAST, &cqr->flags);

	cqr->startdev = memdev;
	cqr->memdev = memdev;
	cqr->block = block;
	cqr->expires = memdev->default_expires * HZ;	/* default 5 minutes */
	cqr->retries = memdev->default_retries;
	cqr->buildclk = get_tod_clock();
	cqr->status = DASD_CQR_FILLED;

	return cqr;
}