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
struct swim_priv {int dummy; } ;
struct request_queue {struct swim_priv* queuedata; } ;
struct request {int /*<<< orphan*/  bio; TYPE_1__* rq_disk; } ;
struct floppy_state {scalar_t__ total_secs; scalar_t__ write_protected; int /*<<< orphan*/  disk_in; } ;
typedef  int /*<<< orphan*/  blk_status_t ;
struct TYPE_2__ {struct floppy_state* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_IOERR ; 
#define  READ 129 
#define  WRITE 128 
 int /*<<< orphan*/  __blk_end_request_cur (struct request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_rq_cur_sectors (struct request*) ; 
 scalar_t__ blk_rq_pos (struct request*) ; 
 int /*<<< orphan*/  floppy_read_sectors (struct floppy_state*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rq_data_dir (struct request*) ; 
 struct request* swim_next_request (struct swim_priv*) ; 

__attribute__((used)) static void do_fd_request(struct request_queue *q)
{
	struct swim_priv *swd = q->queuedata;
	struct request *req;
	struct floppy_state *fs;

	req = swim_next_request(swd);
	while (req) {
		blk_status_t err = BLK_STS_IOERR;

		fs = req->rq_disk->private_data;
		if (blk_rq_pos(req) >= fs->total_secs)
			goto done;
		if (!fs->disk_in)
			goto done;
		if (rq_data_dir(req) == WRITE && fs->write_protected)
			goto done;

		switch (rq_data_dir(req)) {
		case WRITE:
			/* NOT IMPLEMENTED */
			break;
		case READ:
			err = floppy_read_sectors(fs, blk_rq_pos(req),
						  blk_rq_cur_sectors(req),
						  bio_data(req->bio));
			break;
		}
	done:
		if (!__blk_end_request_cur(req, err))
			req = swim_next_request(swd);
	}
}