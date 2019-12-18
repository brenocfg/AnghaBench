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
struct vrfb {unsigned int yoffset; unsigned int xoffset; unsigned int bytespp; } ;
struct omapfb_info {TYPE_1__* region; } ;
struct TYPE_2__ {struct vrfb vrfb; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  FB_ROTATE_CCW 131 
#define  FB_ROTATE_CW 130 
#define  FB_ROTATE_UD 129 
#define  FB_ROTATE_UR 128 
 unsigned int OMAP_VRFB_LINE_LEN ; 

__attribute__((used)) static unsigned omapfb_get_vrfb_offset(const struct omapfb_info *ofbi, int rot)
{
	const struct vrfb *vrfb = &ofbi->region->vrfb;
	unsigned offset;

	switch (rot) {
	case FB_ROTATE_UR:
		offset = 0;
		break;
	case FB_ROTATE_CW:
		offset = vrfb->yoffset;
		break;
	case FB_ROTATE_UD:
		offset = vrfb->yoffset * OMAP_VRFB_LINE_LEN + vrfb->xoffset;
		break;
	case FB_ROTATE_CCW:
		offset = vrfb->xoffset * OMAP_VRFB_LINE_LEN;
		break;
	default:
		BUG();
		return 0;
	}

	offset *= vrfb->bytespp;

	return offset;
}