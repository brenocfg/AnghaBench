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
struct v4l2_sliced_vbi_data {int id; int* data; int /*<<< orphan*/  field; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
#define  V4L2_SLICED_CAPTION_525 129 
#define  V4L2_SLICED_WSS_625 128 
 int saa711x_read (struct v4l2_subdev*,int) ; 

__attribute__((used)) static int saa711x_g_vbi_data(struct v4l2_subdev *sd, struct v4l2_sliced_vbi_data *data)
{
	/* Note: the internal field ID is inverted for NTSC,
	   so data->field 0 maps to the saa7115 even field,
	   whereas for PAL it maps to the saa7115 odd field. */
	switch (data->id) {
	case V4L2_SLICED_WSS_625:
		if (saa711x_read(sd, 0x6b) & 0xc0)
			return -EIO;
		data->data[0] = saa711x_read(sd, 0x6c);
		data->data[1] = saa711x_read(sd, 0x6d);
		return 0;
	case V4L2_SLICED_CAPTION_525:
		if (data->field == 0) {
			/* CC */
			if (saa711x_read(sd, 0x66) & 0x30)
				return -EIO;
			data->data[0] = saa711x_read(sd, 0x69);
			data->data[1] = saa711x_read(sd, 0x6a);
			return 0;
		}
		/* XDS */
		if (saa711x_read(sd, 0x66) & 0xc0)
			return -EIO;
		data->data[0] = saa711x_read(sd, 0x67);
		data->data[1] = saa711x_read(sd, 0x68);
		return 0;
	default:
		return -EINVAL;
	}
}