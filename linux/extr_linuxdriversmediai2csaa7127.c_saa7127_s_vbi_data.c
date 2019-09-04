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
struct v4l2_sliced_vbi_data {int id; int /*<<< orphan*/  field; } ;

/* Variables and functions */
 int EINVAL ; 
#define  V4L2_SLICED_CAPTION_525 130 
#define  V4L2_SLICED_VPS 129 
#define  V4L2_SLICED_WSS_625 128 
 int saa7127_set_cc (struct v4l2_subdev*,struct v4l2_sliced_vbi_data const*) ; 
 int saa7127_set_vps (struct v4l2_subdev*,struct v4l2_sliced_vbi_data const*) ; 
 int saa7127_set_wss (struct v4l2_subdev*,struct v4l2_sliced_vbi_data const*) ; 
 int saa7127_set_xds (struct v4l2_subdev*,struct v4l2_sliced_vbi_data const*) ; 

__attribute__((used)) static int saa7127_s_vbi_data(struct v4l2_subdev *sd, const struct v4l2_sliced_vbi_data *data)
{
	switch (data->id) {
	case V4L2_SLICED_WSS_625:
		return saa7127_set_wss(sd, data);
	case V4L2_SLICED_VPS:
		return saa7127_set_vps(sd, data);
	case V4L2_SLICED_CAPTION_525:
		if (data->field == 0)
			return saa7127_set_cc(sd, data);
		return saa7127_set_xds(sd, data);
	default:
		return -EINVAL;
	}
	return 0;
}