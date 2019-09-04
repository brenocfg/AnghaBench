#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  char request ;
struct floppy_state {char* state; char* cur_req; size_t index; scalar_t__ total_secs; scalar_t__ write_prot; long req_cyl; long secpercyl; unsigned long head; unsigned long secpertrack; unsigned long req_sector; scalar_t__ retries; scalar_t__ ejected; TYPE_1__* mdev; int /*<<< orphan*/  wait; scalar_t__ wanted; } ;
struct TYPE_4__ {int /*<<< orphan*/  queue; } ;
struct TYPE_3__ {scalar_t__ media_bay; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_IOERR ; 
 scalar_t__ MB_FD ; 
 scalar_t__ WRITE ; 
 int /*<<< orphan*/  WRITE_PROT ; 
 int /*<<< orphan*/  act (struct floppy_state*) ; 
 scalar_t__ available ; 
 char* blk_fetch_request (int /*<<< orphan*/ ) ; 
 scalar_t__ blk_rq_pos (char*) ; 
 scalar_t__ check_media_bay (scalar_t__) ; 
 TYPE_2__** disks ; 
 scalar_t__ do_transfer ; 
 scalar_t__ idle ; 
 scalar_t__ rq_data_dir (char*) ; 
 int /*<<< orphan*/  swim3_dbg (char*,...) ; 
 int /*<<< orphan*/  swim3_end_request (struct floppy_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ swim3_readbit (struct floppy_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void start_request(struct floppy_state *fs)
{
	struct request *req;
	unsigned long x;

	swim3_dbg("start request, initial state=%d\n", fs->state);

	if (fs->state == idle && fs->wanted) {
		fs->state = available;
		wake_up(&fs->wait);
		return;
	}
	while (fs->state == idle) {
		swim3_dbg("start request, idle loop, cur_req=%p\n", fs->cur_req);
		if (!fs->cur_req) {
			fs->cur_req = blk_fetch_request(disks[fs->index]->queue);
			swim3_dbg("  fetched request %p\n", fs->cur_req);
			if (!fs->cur_req)
				break;
		}
		req = fs->cur_req;

		if (fs->mdev->media_bay &&
		    check_media_bay(fs->mdev->media_bay) != MB_FD) {
			swim3_dbg("%s", "  media bay absent, dropping req\n");
			swim3_end_request(fs, BLK_STS_IOERR, 0);
			continue;
		}

#if 0 /* This is really too verbose */
		swim3_dbg("do_fd_req: dev=%s cmd=%d sec=%ld nr_sec=%u buf=%p\n",
			  req->rq_disk->disk_name, req->cmd,
			  (long)blk_rq_pos(req), blk_rq_sectors(req),
			  bio_data(req->bio));
		swim3_dbg("           current_nr_sectors=%u\n",
			  blk_rq_cur_sectors(req));
#endif

		if (blk_rq_pos(req) >= fs->total_secs) {
			swim3_dbg("  pos out of bounds (%ld, max is %ld)\n",
				  (long)blk_rq_pos(req), (long)fs->total_secs);
			swim3_end_request(fs, BLK_STS_IOERR, 0);
			continue;
		}
		if (fs->ejected) {
			swim3_dbg("%s", "  disk ejected\n");
			swim3_end_request(fs, BLK_STS_IOERR, 0);
			continue;
		}

		if (rq_data_dir(req) == WRITE) {
			if (fs->write_prot < 0)
				fs->write_prot = swim3_readbit(fs, WRITE_PROT);
			if (fs->write_prot) {
				swim3_dbg("%s", "  try to write, disk write protected\n");
				swim3_end_request(fs, BLK_STS_IOERR, 0);
				continue;
			}
		}

		/* Do not remove the cast. blk_rq_pos(req) is now a
		 * sector_t and can be 64 bits, but it will never go
		 * past 32 bits for this driver anyway, so we can
		 * safely cast it down and not have to do a 64/32
		 * division
		 */
		fs->req_cyl = ((long)blk_rq_pos(req)) / fs->secpercyl;
		x = ((long)blk_rq_pos(req)) % fs->secpercyl;
		fs->head = x / fs->secpertrack;
		fs->req_sector = x % fs->secpertrack + 1;
		fs->state = do_transfer;
		fs->retries = 0;

		act(fs);
	}
}