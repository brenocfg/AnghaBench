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
struct videobuf_queue {struct bttv_fh* priv_data; } ;
struct TYPE_4__ {int /*<<< orphan*/ * count; int /*<<< orphan*/ * start; int /*<<< orphan*/  samples_per_line; } ;
struct TYPE_3__ {TYPE_2__ fmt; } ;
struct bttv_fh {TYPE_1__ vbi_fmt; struct bttv* btv; } ;
struct bttv {int dummy; } ;

/* Variables and functions */
 unsigned int IMAGE_SIZE (TYPE_2__*) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int vbibufs ; 

__attribute__((used)) static int vbi_buffer_setup(struct videobuf_queue *q,
			    unsigned int *count, unsigned int *size)
{
	struct bttv_fh *fh = q->priv_data;
	struct bttv *btv = fh->btv;

	if (0 == *count)
		*count = vbibufs;

	*size = IMAGE_SIZE(&fh->vbi_fmt.fmt);

	dprintk("setup: samples=%u start=%d,%d count=%u,%u\n",
		fh->vbi_fmt.fmt.samples_per_line,
		fh->vbi_fmt.fmt.start[0],
		fh->vbi_fmt.fmt.start[1],
		fh->vbi_fmt.fmt.count[0],
		fh->vbi_fmt.fmt.count[1]);

	return 0;
}