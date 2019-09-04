#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int* start; void** count; int /*<<< orphan*/  sampling_rate; } ;
struct TYPE_12__ {TYPE_5__ vbi; } ;
struct v4l2_format {TYPE_6__ fmt; } ;
struct file {int dummy; } ;
struct TYPE_8__ {int top; int height; } ;
struct TYPE_9__ {TYPE_2__ bounds; } ;
struct bttv_tvnorm {int* vbistart; int /*<<< orphan*/  Fsc; TYPE_3__ cropcap; } ;
struct TYPE_10__ {struct bttv_tvnorm const* tvnorm; TYPE_5__ fmt; } ;
struct bttv_fh {TYPE_4__ vbi_fmt; TYPE_1__* btv; } ;
typedef  int __s32 ;
struct TYPE_7__ {size_t tvnorm; } ;

/* Variables and functions */
 struct bttv_tvnorm* bttv_tvnorms ; 
 void* min (int,int) ; 

int bttv_g_fmt_vbi_cap(struct file *file, void *f, struct v4l2_format *frt)
{
	struct bttv_fh *fh = f;
	const struct bttv_tvnorm *tvnorm;

	frt->fmt.vbi = fh->vbi_fmt.fmt;

	tvnorm = &bttv_tvnorms[fh->btv->tvnorm];

	if (tvnorm != fh->vbi_fmt.tvnorm) {
		__s32 max_end;
		unsigned int i;

		/* As in vbi_buffer_prepare() this imitates the
		   behaviour of earlier driver versions after video
		   standard changes, with default parameters anyway. */

		max_end = (tvnorm->cropcap.bounds.top
			   + tvnorm->cropcap.bounds.height) >> 1;

		frt->fmt.vbi.sampling_rate = tvnorm->Fsc;

		for (i = 0; i < 2; ++i) {
			__s32 new_start;

			new_start = frt->fmt.vbi.start[i]
				+ tvnorm->vbistart[i]
				- fh->vbi_fmt.tvnorm->vbistart[i];

			frt->fmt.vbi.start[i] = min(new_start, max_end - 1);
			frt->fmt.vbi.count[i] =
				min((__s32) frt->fmt.vbi.count[i],
					  max_end - frt->fmt.vbi.start[i]);

			max_end += tvnorm->vbistart[1]
				- tvnorm->vbistart[0];
		}
	}
	return 0;
}