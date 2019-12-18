#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int v4l2_std_id ;
struct v4l2_standard {unsigned int index; } ;
struct TYPE_2__ {int std; char* descr; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODATA ; 
 int V4L2_STD_NTSC ; 
 int V4L2_STD_PAL ; 
 int V4L2_STD_SECAM ; 
 TYPE_1__* standards ; 
 int /*<<< orphan*/  v4l2_video_std_construct (struct v4l2_standard*,int,char const*) ; 

int v4l_video_std_enumstd(struct v4l2_standard *vs, v4l2_std_id id)
{
	v4l2_std_id curr_id = 0;
	unsigned int index = vs->index, i, j = 0;
	const char *descr = "";

	/* Return -ENODATA if the id for the current input
	   or output is 0, meaning that it doesn't support this API. */
	if (id == 0)
		return -ENODATA;

	/* Return norm array in a canonical way */
	for (i = 0; i <= index && id; i++) {
		/* last std value in the standards array is 0, so this
		   while always ends there since (id & 0) == 0. */
		while ((id & standards[j].std) != standards[j].std)
			j++;
		curr_id = standards[j].std;
		descr = standards[j].descr;
		j++;
		if (curr_id == 0)
			break;
		if (curr_id != V4L2_STD_PAL &&
				curr_id != V4L2_STD_SECAM &&
				curr_id != V4L2_STD_NTSC)
			id &= ~curr_id;
	}
	if (i <= index)
		return -EINVAL;

	v4l2_video_std_construct(vs, curr_id, descr);
	return 0;
}