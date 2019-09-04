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
typedef  int u8 ;
struct v4l2_subdev {int dummy; } ;
struct tw9903 {int norm; } ;

/* Variables and functions */
 int V4L2_STD_525_60 ; 
 struct tw9903* to_state (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  write_regs (struct v4l2_subdev*,int const*) ; 

__attribute__((used)) static int tw9903_s_std(struct v4l2_subdev *sd, v4l2_std_id norm)
{
	struct tw9903 *dec = to_state(sd);
	bool is_60hz = norm & V4L2_STD_525_60;
	static const u8 config_60hz[] = {
		0x05, 0x80,
		0x07, 0x02,
		0x08, 0x14,
		0x09, 0xf0,
		0,    0,
	};
	static const u8 config_50hz[] = {
		0x05, 0x00,
		0x07, 0x12,
		0x08, 0x18,
		0x09, 0x20,
		0,    0,
	};

	write_regs(sd, is_60hz ? config_60hz : config_50hz);
	dec->norm = norm;
	return 0;
}