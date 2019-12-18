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
typedef  int u8 ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  afe_write (struct v4l2_subdev*,int,int) ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  io_write (struct v4l2_subdev*,int,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int sdp_io_read (struct v4l2_subdev*,int) ; 
 int /*<<< orphan*/  sdp_io_write (struct v4l2_subdev*,int,int) ; 
 int /*<<< orphan*/  sdp_write (struct v4l2_subdev*,int,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*,int,int,int,int) ; 

__attribute__((used)) static int adv7842_ddr_ram_test(struct v4l2_subdev *sd)
{
	/*
	 * From ADV784x external Memory test.pdf
	 *
	 * Reset must just been performed before running test.
	 * Recommended to reset after test.
	 */
	int i;
	int pass = 0;
	int fail = 0;
	int complete = 0;

	io_write(sd, 0x00, 0x01);  /* Program SDP 4x1 */
	io_write(sd, 0x01, 0x00);  /* Program SDP mode */
	afe_write(sd, 0x80, 0x92); /* SDP Recommended Write */
	afe_write(sd, 0x9B, 0x01); /* SDP Recommended Write ADV7844ES1 */
	afe_write(sd, 0x9C, 0x60); /* SDP Recommended Write ADV7844ES1 */
	afe_write(sd, 0x9E, 0x02); /* SDP Recommended Write ADV7844ES1 */
	afe_write(sd, 0xA0, 0x0B); /* SDP Recommended Write ADV7844ES1 */
	afe_write(sd, 0xC3, 0x02); /* Memory BIST Initialisation */
	io_write(sd, 0x0C, 0x40);  /* Power up ADV7844 */
	io_write(sd, 0x15, 0xBA);  /* Enable outputs */
	sdp_write(sd, 0x12, 0x00); /* Disable 3D comb, Frame TBC & 3DNR */
	io_write(sd, 0xFF, 0x04);  /* Reset memory controller */

	usleep_range(5000, 6000);

	sdp_write(sd, 0x12, 0x00);    /* Disable 3D Comb, Frame TBC & 3DNR */
	sdp_io_write(sd, 0x2A, 0x01); /* Memory BIST Initialisation */
	sdp_io_write(sd, 0x7c, 0x19); /* Memory BIST Initialisation */
	sdp_io_write(sd, 0x80, 0x87); /* Memory BIST Initialisation */
	sdp_io_write(sd, 0x81, 0x4a); /* Memory BIST Initialisation */
	sdp_io_write(sd, 0x82, 0x2c); /* Memory BIST Initialisation */
	sdp_io_write(sd, 0x83, 0x0e); /* Memory BIST Initialisation */
	sdp_io_write(sd, 0x84, 0x94); /* Memory BIST Initialisation */
	sdp_io_write(sd, 0x85, 0x62); /* Memory BIST Initialisation */
	sdp_io_write(sd, 0x7d, 0x00); /* Memory BIST Initialisation */
	sdp_io_write(sd, 0x7e, 0x1a); /* Memory BIST Initialisation */

	usleep_range(5000, 6000);

	sdp_io_write(sd, 0xd9, 0xd5); /* Enable BIST Test */
	sdp_write(sd, 0x12, 0x05); /* Enable FRAME TBC & 3D COMB */

	msleep(20);

	for (i = 0; i < 10; i++) {
		u8 result = sdp_io_read(sd, 0xdb);
		if (result & 0x10) {
			complete++;
			if (result & 0x20)
				fail++;
			else
				pass++;
		}
		msleep(20);
	}

	v4l2_dbg(1, debug, sd,
		"Ram Test: completed %d of %d: pass %d, fail %d\n",
		complete, i, pass, fail);

	if (!complete || fail)
		return -EIO;
	return 0;
}