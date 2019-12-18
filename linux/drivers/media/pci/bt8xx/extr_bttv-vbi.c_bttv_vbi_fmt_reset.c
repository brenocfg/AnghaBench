#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int samples_per_line; int* start; unsigned int* count; scalar_t__* reserved; scalar_t__ flags; int /*<<< orphan*/  offset; int /*<<< orphan*/  sample_format; int /*<<< orphan*/  sampling_rate; } ;
struct bttv_vbi_fmt {int end; struct bttv_tvnorm const* tvnorm; TYPE_1__ fmt; } ;
struct TYPE_5__ {int top; } ;
struct TYPE_6__ {TYPE_2__ defrect; } ;
struct bttv_tvnorm {int* vbistart; int vbipack; TYPE_3__ cropcap; int /*<<< orphan*/  Fsc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_GREY ; 
 unsigned int VBI_BPL ; 
 unsigned int VBI_DEFLINES ; 
 int /*<<< orphan*/  VBI_OFFSET ; 
 struct bttv_tvnorm* bttv_tvnorms ; 

void bttv_vbi_fmt_reset(struct bttv_vbi_fmt *f, unsigned int norm)
{
	const struct bttv_tvnorm *tvnorm;
	unsigned int real_samples_per_line;
	unsigned int real_count;

	tvnorm = &bttv_tvnorms[norm];

	f->fmt.sampling_rate    = tvnorm->Fsc;
	f->fmt.samples_per_line = VBI_BPL;
	f->fmt.sample_format    = V4L2_PIX_FMT_GREY;
	f->fmt.offset           = VBI_OFFSET;
	f->fmt.start[0]		= tvnorm->vbistart[0];
	f->fmt.start[1]		= tvnorm->vbistart[1];
	f->fmt.count[0]		= VBI_DEFLINES;
	f->fmt.count[1]		= VBI_DEFLINES;
	f->fmt.flags            = 0;
	f->fmt.reserved[0]      = 0;
	f->fmt.reserved[1]      = 0;

	/* For compatibility the buffer size must be 2 * VBI_DEFLINES *
	   VBI_BPL regardless of the current video standard. */
	real_samples_per_line   = 1024 + tvnorm->vbipack * 4;
	real_count              = ((tvnorm->cropcap.defrect.top >> 1)
				   - tvnorm->vbistart[0]);

	BUG_ON(real_samples_per_line > VBI_BPL);
	BUG_ON(real_count > VBI_DEFLINES);

	f->tvnorm               = tvnorm;

	/* See bttv_vbi_fmt_set(). */
	f->end                  = tvnorm->vbistart[0] * 2 + 2;
}