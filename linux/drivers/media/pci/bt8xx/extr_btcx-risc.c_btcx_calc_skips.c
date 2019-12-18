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
struct TYPE_2__ {int left; int width; int top; int height; } ;
struct v4l2_clip {TYPE_1__ c; } ;
struct btcx_skiplist {int end; scalar_t__ start; } ;

/* Variables and functions */
 scalar_t__ btcx_debug ; 
 int /*<<< orphan*/  dprintk (char*,int,int) ; 
 int /*<<< orphan*/  pr_cont (char*,...) ; 

void
btcx_calc_skips(int line, int width, int *maxy,
		struct btcx_skiplist *skips, unsigned int *nskips,
		const struct v4l2_clip *clips, unsigned int nclips)
{
	unsigned int clip,skip;
	int end, maxline;

	skip=0;
	maxline = 9999;
	for (clip = 0; clip < nclips; clip++) {

		/* sanity checks */
		if (clips[clip].c.left + clips[clip].c.width <= 0)
			continue;
		if (clips[clip].c.left > (signed)width)
			break;

		/* vertical range */
		if (line > clips[clip].c.top+clips[clip].c.height-1)
			continue;
		if (line < clips[clip].c.top) {
			if (maxline > clips[clip].c.top-1)
				maxline = clips[clip].c.top-1;
			continue;
		}
		if (maxline > clips[clip].c.top+clips[clip].c.height-1)
			maxline = clips[clip].c.top+clips[clip].c.height-1;

		/* horizontal range */
		if (0 == skip || clips[clip].c.left > skips[skip-1].end) {
			/* new one */
			skips[skip].start = clips[clip].c.left;
			if (skips[skip].start < 0)
				skips[skip].start = 0;
			skips[skip].end = clips[clip].c.left + clips[clip].c.width;
			if (skips[skip].end > width)
				skips[skip].end = width;
			skip++;
		} else {
			/* overlaps -- expand last one */
			end = clips[clip].c.left + clips[clip].c.width;
			if (skips[skip-1].end < end)
				skips[skip-1].end = end;
			if (skips[skip-1].end > width)
				skips[skip-1].end = width;
		}
	}
	*nskips = skip;
	*maxy = maxline;

	if (btcx_debug) {
		dprintk("btcx: skips line %d-%d:", line, maxline);
		for (skip = 0; skip < *nskips; skip++) {
			pr_cont(" %d-%d", skips[skip].start, skips[skip].end);
		}
		pr_cont("\n");
	}
}