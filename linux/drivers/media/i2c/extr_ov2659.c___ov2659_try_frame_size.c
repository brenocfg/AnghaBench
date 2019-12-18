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
struct v4l2_mbus_framefmt {scalar_t__ height; scalar_t__ width; } ;
struct ov2659_framesize {scalar_t__ height; scalar_t__ width; TYPE_1__* regs; } ;
struct TYPE_2__ {scalar_t__ addr; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct ov2659_framesize*) ; 
 unsigned int UINT_MAX ; 
 int abs (scalar_t__) ; 
 struct ov2659_framesize* ov2659_framesizes ; 

__attribute__((used)) static void __ov2659_try_frame_size(struct v4l2_mbus_framefmt *mf,
				    const struct ov2659_framesize **size)
{
	const struct ov2659_framesize *fsize = &ov2659_framesizes[0];
	const struct ov2659_framesize *match = NULL;
	int i = ARRAY_SIZE(ov2659_framesizes);
	unsigned int min_err = UINT_MAX;

	while (i--) {
		int err = abs(fsize->width - mf->width)
				+ abs(fsize->height - mf->height);
		if ((err < min_err) && (fsize->regs[0].addr)) {
			min_err = err;
			match = fsize;
		}
		fsize++;
	}

	if (!match)
		match = &ov2659_framesizes[2];

	mf->width  = match->width;
	mf->height = match->height;

	if (size)
		*size = match;
}