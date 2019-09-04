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
struct v4l2_rect {int left; int width; int /*<<< orphan*/  top; int /*<<< orphan*/  height; } ;
struct TYPE_2__ {int left; int width; int /*<<< orphan*/  top; int /*<<< orphan*/  height; } ;
struct v4l2_clip {TYPE_1__ c; } ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (char*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,...) ; 

int
btcx_align(struct v4l2_rect *win, struct v4l2_clip *clips, unsigned int n, int mask)
{
	s32 nx,nw,dx;
	unsigned int i;

	/* fixup window */
	nx = (win->left + mask) & ~mask;
	nw = (win->width) & ~mask;
	if (nx + nw > win->left + win->width)
		nw -= mask+1;
	dx = nx - win->left;
	win->left  = nx;
	win->width = nw;
	dprintk("btcx: window align %dx%d+%d+%d [dx=%d]\n",
	       win->width, win->height, win->left, win->top, dx);

	/* fixup clips */
	for (i = 0; i < n; i++) {
		nx = (clips[i].c.left-dx) & ~mask;
		nw = (clips[i].c.width) & ~mask;
		if (nx + nw < clips[i].c.left-dx + clips[i].c.width)
			nw += mask+1;
		clips[i].c.left  = nx;
		clips[i].c.width = nw;
		dprintk("btcx:   clip align %dx%d+%d+%d\n",
		       clips[i].c.width, clips[i].c.height,
		       clips[i].c.left, clips[i].c.top);
	}
	return 0;
}