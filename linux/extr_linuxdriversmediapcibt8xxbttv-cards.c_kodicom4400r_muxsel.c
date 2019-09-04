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
struct TYPE_2__ {size_t nr; } ;
struct bttv {int* sw_status; TYPE_1__ c; } ;

/* Variables and functions */
 int /*<<< orphan*/  kodicom4400r_write (struct bttv*,int,int,int) ; 
 struct bttv** master ; 

__attribute__((used)) static void kodicom4400r_muxsel(struct bttv *btv, unsigned int input)
{
	int xaddr, yaddr;
	struct bttv *mctlr;
	static unsigned char map[4] = {3, 0, 2, 1};

	mctlr = master[btv->c.nr];
	if (mctlr == NULL) {	/* ignore if master not yet detected */
		return;
	}
	yaddr = (btv->c.nr - mctlr->c.nr + 1) & 3; /* the '&' is for safety */
	yaddr = map[yaddr];
	xaddr = input & 0xf;
	/* Check if the controller/camera pair has changed, else ignore */
	if (mctlr->sw_status[yaddr] != xaddr)
	{
		/* "open" the old switch, "close" the new one, save the new */
		kodicom4400r_write(mctlr, mctlr->sw_status[yaddr], yaddr, 0);
		mctlr->sw_status[yaddr] = xaddr;
		kodicom4400r_write(mctlr, xaddr, yaddr, 1);
	}
}