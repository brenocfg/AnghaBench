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
struct v4l2_tuner {int audmode; scalar_t__ index; } ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SWITCH ; 
 int TDA9840_SET_BOTH ; 
 int TDA9840_SET_LANG1 ; 
 int TDA9840_SET_LANG2 ; 
 int TDA9840_SET_MONO ; 
 int TDA9840_SET_STEREO ; 
#define  V4L2_TUNER_MODE_LANG1_LANG2 129 
#define  V4L2_TUNER_MODE_LANG2 128 
 int V4L2_TUNER_MODE_MONO ; 
 int /*<<< orphan*/  debug ; 
 int tda9840_status (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  tda9840_write (struct v4l2_subdev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*,int) ; 

__attribute__((used)) static int tda9840_s_tuner(struct v4l2_subdev *sd, const struct v4l2_tuner *t)
{
	int stat = tda9840_status(sd);
	int byte;

	if (t->index)
		return -EINVAL;

	stat = stat < 0 ? 0 : stat;
	if (stat == 0 || stat == 0x60) /* mono input */
		byte = TDA9840_SET_MONO;
	else if (stat == 0x40) /* stereo input */
		byte = (t->audmode == V4L2_TUNER_MODE_MONO) ?
			TDA9840_SET_MONO : TDA9840_SET_STEREO;
	else { /* bilingual */
		switch (t->audmode) {
		case V4L2_TUNER_MODE_LANG1_LANG2:
			byte = TDA9840_SET_BOTH;
			break;
		case V4L2_TUNER_MODE_LANG2:
			byte = TDA9840_SET_LANG2;
			break;
		default:
			byte = TDA9840_SET_LANG1;
			break;
		}
	}
	v4l2_dbg(1, debug, sd, "TDA9840_SWITCH: 0x%02x\n", byte);
	tda9840_write(sd, SWITCH, byte);
	return 0;
}