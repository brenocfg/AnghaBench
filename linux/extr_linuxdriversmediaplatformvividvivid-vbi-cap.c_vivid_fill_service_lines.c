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
struct v4l2_sliced_vbi_format {int io_size; int service_set; int** service_lines; int** reserved; } ;
struct v4l2_sliced_vbi_data {int dummy; } ;

/* Variables and functions */
 int V4L2_SLICED_CAPTION_525 ; 
 int V4L2_SLICED_TELETEXT_B ; 
 int V4L2_SLICED_WSS_625 ; 
 int /*<<< orphan*/  memset (int**,int /*<<< orphan*/ ,int) ; 

void vivid_fill_service_lines(struct v4l2_sliced_vbi_format *vbi, u32 service_set)
{
	vbi->io_size = sizeof(struct v4l2_sliced_vbi_data) * 36;
	vbi->service_set = service_set;
	memset(vbi->service_lines, 0, sizeof(vbi->service_lines));
	memset(vbi->reserved, 0, sizeof(vbi->reserved));

	if (vbi->service_set == 0)
		return;

	if (vbi->service_set & V4L2_SLICED_CAPTION_525) {
		vbi->service_lines[0][21] = V4L2_SLICED_CAPTION_525;
		vbi->service_lines[1][21] = V4L2_SLICED_CAPTION_525;
	}
	if (vbi->service_set & V4L2_SLICED_WSS_625) {
		unsigned i;

		for (i = 7; i <= 18; i++)
			vbi->service_lines[0][i] =
			vbi->service_lines[1][i] = V4L2_SLICED_TELETEXT_B;
		vbi->service_lines[0][23] = V4L2_SLICED_WSS_625;
	}
}