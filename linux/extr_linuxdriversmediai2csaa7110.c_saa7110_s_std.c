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
typedef  int v4l2_std_id ;
struct v4l2_subdev {int dummy; } ;
struct saa7110 {int norm; } ;

/* Variables and functions */
 int EINVAL ; 
 int V4L2_STD_NTSC ; 
 int V4L2_STD_PAL ; 
 int V4L2_STD_SECAM ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  saa7110_write (struct v4l2_subdev*,int,int) ; 
 struct saa7110* to_saa7110 (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*) ; 

__attribute__((used)) static int saa7110_s_std(struct v4l2_subdev *sd, v4l2_std_id std)
{
	struct saa7110 *decoder = to_saa7110(sd);

	if (decoder->norm != std) {
		decoder->norm = std;
		/*saa7110_write(sd, 0x06, 0x03);*/
		if (std & V4L2_STD_NTSC) {
			saa7110_write(sd, 0x0D, 0x86);
			saa7110_write(sd, 0x0F, 0x50);
			saa7110_write(sd, 0x11, 0x2C);
			/*saa7110_write(sd, 0x2E, 0x81);*/
			v4l2_dbg(1, debug, sd, "switched to NTSC\n");
		} else if (std & V4L2_STD_PAL) {
			saa7110_write(sd, 0x0D, 0x86);
			saa7110_write(sd, 0x0F, 0x10);
			saa7110_write(sd, 0x11, 0x59);
			/*saa7110_write(sd, 0x2E, 0x9A);*/
			v4l2_dbg(1, debug, sd, "switched to PAL\n");
		} else if (std & V4L2_STD_SECAM) {
			saa7110_write(sd, 0x0D, 0x87);
			saa7110_write(sd, 0x0F, 0x10);
			saa7110_write(sd, 0x11, 0x59);
			/*saa7110_write(sd, 0x2E, 0x9A);*/
			v4l2_dbg(1, debug, sd, "switched to SECAM\n");
		} else {
			return -EINVAL;
		}
	}
	return 0;
}