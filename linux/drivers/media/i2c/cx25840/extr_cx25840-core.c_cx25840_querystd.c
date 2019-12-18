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
typedef  scalar_t__ v4l2_std_id ;
typedef  size_t u32 ;
struct v4l2_subdev {int dummy; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
#define  V4L2_STD_NTSC_443 137 
#define  V4L2_STD_NTSC_M 136 
#define  V4L2_STD_NTSC_M_JP 135 
#define  V4L2_STD_PAL 134 
#define  V4L2_STD_PAL_60 133 
#define  V4L2_STD_PAL_M 132 
#define  V4L2_STD_PAL_N 131 
#define  V4L2_STD_PAL_Nc 130 
#define  V4L2_STD_SECAM 129 
#define  V4L2_STD_UNKNOWN 128 
 int /*<<< orphan*/  cx25840_debug ; 
 int cx25840_read4 (struct i2c_client*,int) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l_dbg (int,int /*<<< orphan*/ ,struct i2c_client*,char*,size_t,unsigned int) ; 

__attribute__((used)) static int cx25840_querystd(struct v4l2_subdev *sd, v4l2_std_id *std)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);

	static const v4l2_std_id stds[] = {
		/* 0000 */ V4L2_STD_UNKNOWN,

		/* 0001 */ V4L2_STD_NTSC_M,
		/* 0010 */ V4L2_STD_NTSC_M_JP,
		/* 0011 */ V4L2_STD_NTSC_443,
		/* 0100 */ V4L2_STD_PAL,
		/* 0101 */ V4L2_STD_PAL_M,
		/* 0110 */ V4L2_STD_PAL_N,
		/* 0111 */ V4L2_STD_PAL_Nc,
		/* 1000 */ V4L2_STD_PAL_60,

		/* 1001 */ V4L2_STD_UNKNOWN,
		/* 1010 */ V4L2_STD_UNKNOWN,
		/* 1011 */ V4L2_STD_UNKNOWN,
		/* 1100 */ V4L2_STD_SECAM,
		/* 1101 */ V4L2_STD_UNKNOWN,
		/* 1110 */ V4L2_STD_UNKNOWN,
		/* 1111 */ V4L2_STD_UNKNOWN
	};

	u32 fmt = (cx25840_read4(client, 0x40c) >> 8) & 0xf;
	*std = stds[fmt];

	v4l_dbg(1, cx25840_debug, client,
		"querystd fmt = %x, v4l2_std_id = 0x%x\n",
		fmt, (unsigned int)stds[fmt]);

	return 0;
}