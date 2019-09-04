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
struct TYPE_6__ {scalar_t__ end; } ;
struct bttv_fh {int resources; TYPE_3__ vbi_fmt; int /*<<< orphan*/  do_crop; } ;
struct bttv {int resources; scalar_t__ vbi_end; scalar_t__ crop_start; TYPE_2__* crop; } ;
typedef  scalar_t__ __s32 ;
struct TYPE_4__ {scalar_t__ top; } ;
struct TYPE_5__ {TYPE_1__ rect; } ;

/* Variables and functions */
 int RESOURCE_VIDEO_READ ; 
 int RESOURCE_VIDEO_STREAM ; 
 int VBI_RESOURCES ; 
 int VIDEO_RESOURCES ; 

__attribute__((used)) static
int check_alloc_btres_lock(struct bttv *btv, struct bttv_fh *fh, int bit)
{
	int xbits; /* mutual exclusive resources */

	if (fh->resources & bit)
		/* have it already allocated */
		return 1;

	xbits = bit;
	if (bit & (RESOURCE_VIDEO_READ | RESOURCE_VIDEO_STREAM))
		xbits |= RESOURCE_VIDEO_READ | RESOURCE_VIDEO_STREAM;

	/* is it free? */
	if (btv->resources & xbits) {
		/* no, someone else uses it */
		goto fail;
	}

	if ((bit & VIDEO_RESOURCES)
	    && 0 == (btv->resources & VIDEO_RESOURCES)) {
		/* Do crop - use current, don't - use default parameters. */
		__s32 top = btv->crop[!!fh->do_crop].rect.top;

		if (btv->vbi_end > top)
			goto fail;

		/* We cannot capture the same line as video and VBI data.
		   Claim scan lines crop[].rect.top to bottom. */
		btv->crop_start = top;
	} else if (bit & VBI_RESOURCES) {
		__s32 end = fh->vbi_fmt.end;

		if (end > btv->crop_start)
			goto fail;

		/* Claim scan lines above fh->vbi_fmt.end. */
		btv->vbi_end = end;
	}

	/* it's free, grab it */
	fh->resources  |= bit;
	btv->resources |= bit;
	return 1;

 fail:
	return 0;
}