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
 int /*<<< orphan*/  gv800s_write (struct bttv*,int,int,int) ; 
 struct bttv** master ; 

__attribute__((used)) static void gv800s_muxsel(struct bttv *btv, unsigned int input)
{
	struct bttv *mctlr;
	int xaddr, yaddr;
	static unsigned int map[4][4] = { { 0x0, 0x4, 0xa, 0x6 },
					  { 0x1, 0x5, 0xb, 0x7 },
					  { 0x2, 0x8, 0xc, 0xe },
					  { 0x3, 0x9, 0xd, 0xf } };
	input = input%4;
	mctlr = master[btv->c.nr];
	if (mctlr == NULL) {
		/* do nothing until the "master" is detected */
		return;
	}
	yaddr = (btv->c.nr - mctlr->c.nr) & 3;
	xaddr = map[yaddr][input] & 0xf;

	/* Check if the controller/camera pair has changed, ignore otherwise */
	if (mctlr->sw_status[yaddr] != xaddr) {
		/* disable the old switch, enable the new one and save status */
		gv800s_write(mctlr, mctlr->sw_status[yaddr], yaddr, 0);
		mctlr->sw_status[yaddr] = xaddr;
		gv800s_write(mctlr, xaddr, yaddr, 1);
	}
}