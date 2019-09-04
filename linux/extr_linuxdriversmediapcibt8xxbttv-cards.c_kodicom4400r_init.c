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
struct TYPE_2__ {int nr; } ;
struct bttv {int* sw_status; TYPE_1__ c; } ;

/* Variables and functions */
 int BTTV_MAX ; 
 int /*<<< orphan*/  gpio_inout (int,int) ; 
 int /*<<< orphan*/  gpio_write (int) ; 
 int /*<<< orphan*/  kodicom4400r_write (struct bttv*,int,int,int) ; 
 struct bttv** master ; 

__attribute__((used)) static void kodicom4400r_init(struct bttv *btv)
{
	int ix;

	gpio_inout(0x0003ff, 0x0003ff);
	gpio_write(1 << 9);	/* reset MUX */
	gpio_write(0);
	/* Preset camera 0 to the 4 controllers */
	for (ix = 0; ix < 4; ix++) {
		btv->sw_status[ix] = ix;
		kodicom4400r_write(btv, ix, ix, 1);
	}
	/*
	 * Since this is the "master", we need to set up the
	 * other three controller chips' pointers to this structure
	 * for later use in the muxsel routine.
	 */
	if ((btv->c.nr<1) || (btv->c.nr>BTTV_MAX-3))
	    return;
	master[btv->c.nr-1] = btv;
	master[btv->c.nr]   = btv;
	master[btv->c.nr+1] = btv;
	master[btv->c.nr+2] = btv;
}