#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct v4l2_vbi_format {scalar_t__* count; int* start; scalar_t__* reserved; scalar_t__ flags; int /*<<< orphan*/  offset; int /*<<< orphan*/  sample_format; int /*<<< orphan*/  samples_per_line; int /*<<< orphan*/  sampling_rate; } ;
struct TYPE_3__ {int top; int height; } ;
struct TYPE_4__ {TYPE_1__ bounds; } ;
struct bttv_tvnorm {int* vbistart; int /*<<< orphan*/  Fsc; TYPE_2__ cropcap; } ;
typedef  int s64 ;
typedef  int __s32 ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EBUSY ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_GREY ; 
 int /*<<< orphan*/  VBI_BPL ; 
 int /*<<< orphan*/  VBI_OFFSET ; 
 void* clamp (int,int,int) ; 

__attribute__((used)) static int try_fmt(struct v4l2_vbi_format *f, const struct bttv_tvnorm *tvnorm,
			__s32 crop_start)
{
	__s32 min_start, max_start, max_end, f2_offset;
	unsigned int i;

	/* For compatibility with earlier driver versions we must pretend
	   the VBI and video capture window may overlap. In reality RISC
	   magic aborts VBI capturing at the first line of video capturing,
	   leaving the rest of the buffer unchanged, usually all zero.
	   VBI capturing must always start before video capturing. >> 1
	   because cropping counts field lines times two. */
	min_start = tvnorm->vbistart[0];
	max_start = (crop_start >> 1) - 1;
	max_end = (tvnorm->cropcap.bounds.top
		   + tvnorm->cropcap.bounds.height) >> 1;

	if (min_start > max_start)
		return -EBUSY;

	BUG_ON(max_start >= max_end);

	f->sampling_rate    = tvnorm->Fsc;
	f->samples_per_line = VBI_BPL;
	f->sample_format    = V4L2_PIX_FMT_GREY;
	f->offset           = VBI_OFFSET;

	f2_offset = tvnorm->vbistart[1] - tvnorm->vbistart[0];

	for (i = 0; i < 2; ++i) {
		if (0 == f->count[i]) {
			/* No data from this field. We leave f->start[i]
			   alone because VIDIOCSVBIFMT is w/o and EINVALs
			   when a driver does not support exactly the
			   requested parameters. */
		} else {
			s64 start, count;

			start = clamp(f->start[i], min_start, max_start);
			/* s64 to prevent overflow. */
			count = (s64) f->start[i] + f->count[i] - start;
			f->start[i] = start;
			f->count[i] = clamp(count, (s64) 1,
					    max_end - start);
		}

		min_start += f2_offset;
		max_start += f2_offset;
		max_end += f2_offset;
	}

	if (0 == (f->count[0] | f->count[1])) {
		/* As in earlier driver versions. */
		f->start[0] = tvnorm->vbistart[0];
		f->start[1] = tvnorm->vbistart[1];
		f->count[0] = 1;
		f->count[1] = 1;
	}

	f->flags = 0;

	f->reserved[0] = 0;
	f->reserved[1] = 0;

	return 0;
}