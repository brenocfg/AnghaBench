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
typedef  int /*<<< orphan*/  u32 ;
struct v4l2_subdev {int dummy; } ;
struct bt856 {int norm; } ;

/* Variables and functions */
 int V4L2_STD_NTSC ; 
 int /*<<< orphan*/  bt856_dump (struct bt856*) ; 
 int /*<<< orphan*/  bt856_setbit (struct bt856*,int,int,int) ; 
 int /*<<< orphan*/  bt856_write (struct bt856*,int,int) ; 
 scalar_t__ debug ; 
 struct bt856* to_bt856 (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_dbg (int,scalar_t__,struct v4l2_subdev*,char*) ; 

__attribute__((used)) static int bt856_init(struct v4l2_subdev *sd, u32 arg)
{
	struct bt856 *encoder = to_bt856(sd);

	/* This is just for testing!!! */
	v4l2_dbg(1, debug, sd, "init\n");
	bt856_write(encoder, 0xdc, 0x18);
	bt856_write(encoder, 0xda, 0);
	bt856_write(encoder, 0xde, 0);

	bt856_setbit(encoder, 0xdc, 3, 1);
	/*bt856_setbit(encoder, 0xdc, 6, 0);*/
	bt856_setbit(encoder, 0xdc, 4, 1);

	if (encoder->norm & V4L2_STD_NTSC)
		bt856_setbit(encoder, 0xdc, 2, 0);
	else
		bt856_setbit(encoder, 0xdc, 2, 1);

	bt856_setbit(encoder, 0xdc, 1, 1);
	bt856_setbit(encoder, 0xde, 4, 0);
	bt856_setbit(encoder, 0xde, 3, 1);
	if (debug != 0)
		bt856_dump(encoder);
	return 0;
}