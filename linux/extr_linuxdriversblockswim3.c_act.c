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
struct floppy_state {int state; int req_cyl; int cur_cyl; int expect_cyl; int settle_time; int retries; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_IOERR ; 
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  TRACK_ZERO ; 
#define  do_transfer 133 
#define  idle 132 
#define  jogging 131 
#define  locating 130 
 int /*<<< orphan*/  scan_track (struct floppy_state*) ; 
 int /*<<< orphan*/  seek_track (struct floppy_state*,int) ; 
#define  seeking 129 
 int /*<<< orphan*/  set_timeout (struct floppy_state*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  settle_timeout ; 
#define  settling 128 
 int /*<<< orphan*/  setup_transfer (struct floppy_state*) ; 
 int /*<<< orphan*/  swim3_dbg (char*,...) ; 
 int /*<<< orphan*/  swim3_end_request (struct floppy_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swim3_err (char*,int,...) ; 
 int /*<<< orphan*/  swim3_readbit (struct floppy_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swim3_warn (char*,char*) ; 

__attribute__((used)) static void act(struct floppy_state *fs)
{
	for (;;) {
		swim3_dbg("  act loop, state=%d, req_cyl=%d, cur_cyl=%d\n",
			  fs->state, fs->req_cyl, fs->cur_cyl);

		switch (fs->state) {
		case idle:
			return;		/* XXX shouldn't get here */

		case locating:
			if (swim3_readbit(fs, TRACK_ZERO)) {
				swim3_dbg("%s", "    locate track 0\n");
				fs->cur_cyl = 0;
				if (fs->req_cyl == 0)
					fs->state = do_transfer;
				else
					fs->state = seeking;
				break;
			}
			scan_track(fs);
			return;

		case seeking:
			if (fs->cur_cyl < 0) {
				fs->expect_cyl = -1;
				fs->state = locating;
				break;
			}
			if (fs->req_cyl == fs->cur_cyl) {
				swim3_warn("%s", "Whoops, seeking 0\n");
				fs->state = do_transfer;
				break;
			}
			seek_track(fs, fs->req_cyl - fs->cur_cyl);
			return;

		case settling:
			/* check for SEEK_COMPLETE after 30ms */
			fs->settle_time = (HZ + 32) / 33;
			set_timeout(fs, fs->settle_time, settle_timeout);
			return;

		case do_transfer:
			if (fs->cur_cyl != fs->req_cyl) {
				if (fs->retries > 5) {
					swim3_err("Wrong cylinder in transfer, want: %d got %d\n",
						  fs->req_cyl, fs->cur_cyl);
					swim3_end_request(fs, BLK_STS_IOERR, 0);
					fs->state = idle;
					return;
				}
				fs->state = seeking;
				break;
			}
			setup_transfer(fs);
			return;

		case jogging:
			seek_track(fs, -5);
			return;

		default:
			swim3_err("Unknown state %d\n", fs->state);
			return;
		}
	}
}