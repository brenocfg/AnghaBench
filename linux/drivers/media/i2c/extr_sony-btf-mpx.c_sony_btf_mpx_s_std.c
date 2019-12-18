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
struct sony_btf_mpx {int mpxmode; } ;

/* Variables and functions */
 int V4L2_STD_PAL_BG ; 
 int V4L2_STD_PAL_DK ; 
 int V4L2_STD_PAL_I ; 
 int V4L2_STD_SECAM_L ; 
 int /*<<< orphan*/  mpx_setup (struct sony_btf_mpx*) ; 
 struct sony_btf_mpx* to_state (struct v4l2_subdev*) ; 

__attribute__((used)) static int sony_btf_mpx_s_std(struct v4l2_subdev *sd, v4l2_std_id std)
{
	struct sony_btf_mpx *t = to_state(sd);
	int default_mpx_mode = 0;

	if (std & V4L2_STD_PAL_BG)
		default_mpx_mode = 1;
	else if (std & V4L2_STD_PAL_I)
		default_mpx_mode = 4;
	else if (std & V4L2_STD_PAL_DK)
		default_mpx_mode = 6;
	else if (std & V4L2_STD_SECAM_L)
		default_mpx_mode = 11;

	if (default_mpx_mode != t->mpxmode) {
		t->mpxmode = default_mpx_mode;
		mpx_setup(t);
	}
	return 0;
}