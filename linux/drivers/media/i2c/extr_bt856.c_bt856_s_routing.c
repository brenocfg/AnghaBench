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
typedef  int u32 ;
struct v4l2_subdev {int dummy; } ;
struct bt856 {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  bt856_dump (struct bt856*) ; 
 int /*<<< orphan*/  bt856_setbit (struct bt856*,int,int,int) ; 
 scalar_t__ debug ; 
 struct bt856* to_bt856 (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_dbg (int,scalar_t__,struct v4l2_subdev*,char*,int) ; 

__attribute__((used)) static int bt856_s_routing(struct v4l2_subdev *sd,
			   u32 input, u32 output, u32 config)
{
	struct bt856 *encoder = to_bt856(sd);

	v4l2_dbg(1, debug, sd, "set input %d\n", input);

	/* We only have video bus.
	 * input= 0: input is from bt819
	 * input= 1: input is from ZR36060 */
	switch (input) {
	case 0:
		bt856_setbit(encoder, 0xde, 4, 0);
		bt856_setbit(encoder, 0xde, 3, 1);
		bt856_setbit(encoder, 0xdc, 3, 1);
		bt856_setbit(encoder, 0xdc, 6, 0);
		break;
	case 1:
		bt856_setbit(encoder, 0xde, 4, 0);
		bt856_setbit(encoder, 0xde, 3, 1);
		bt856_setbit(encoder, 0xdc, 3, 1);
		bt856_setbit(encoder, 0xdc, 6, 1);
		break;
	case 2:	/* Color bar */
		bt856_setbit(encoder, 0xdc, 3, 0);
		bt856_setbit(encoder, 0xde, 4, 1);
		break;
	default:
		return -EINVAL;
	}

	if (debug != 0)
		bt856_dump(encoder);
	return 0;
}