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
 int /*<<< orphan*/  sprintf (int*,char*,int) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int,struct v4l2_subdev*,char*,...) ; 

__attribute__((used)) static void adv7511_dbg_dump_edid(int lvl, int debug, struct v4l2_subdev *sd, int segment, u8 *buf)
{
	if (debug >= lvl) {
		int i, j;
		v4l2_dbg(lvl, debug, sd, "edid segment %d\n", segment);
		for (i = 0; i < 256; i += 16) {
			u8 b[128];
			u8 *bp = b;
			if (i == 128)
				v4l2_dbg(lvl, debug, sd, "\n");
			for (j = i; j < i + 16; j++) {
				sprintf(bp, "0x%02x, ", buf[j]);
				bp += 6;
			}
			bp[0] = '\0';
			v4l2_dbg(lvl, debug, sd, "%s\n", b);
		}
	}
}