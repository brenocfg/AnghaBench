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
struct v4l2_subdev {int dummy; } ;
struct saa7110 {int enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  saa7110_write (struct v4l2_subdev*,int,int) ; 
 struct saa7110* to_saa7110 (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*,char*) ; 

__attribute__((used)) static int saa7110_s_stream(struct v4l2_subdev *sd, int enable)
{
	struct saa7110 *decoder = to_saa7110(sd);

	if (decoder->enable != enable) {
		decoder->enable = enable;
		saa7110_write(sd, 0x0E, enable ? 0x18 : 0x80);
		v4l2_dbg(1, debug, sd, "YUV %s\n", enable ? "on" : "off");
	}
	return 0;
}