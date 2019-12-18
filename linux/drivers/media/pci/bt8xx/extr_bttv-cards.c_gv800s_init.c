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
 int /*<<< orphan*/  bttv_I2CWrite (struct bttv*,int,int,int,int) ; 
 int /*<<< orphan*/  gpio_inout (int,int) ; 
 int /*<<< orphan*/  gpio_write (int) ; 
 int /*<<< orphan*/  gv800s_write (struct bttv*,int,int,int) ; 
 struct bttv** master ; 

__attribute__((used)) static void gv800s_init(struct bttv *btv)
{
	int ix;

	gpio_inout(0xf107f, 0xf107f);
	gpio_write(1<<19); /* reset the analog MUX */
	gpio_write(0);

	/* Preset camera 0 to the 4 controllers */
	for (ix = 0; ix < 4; ix++) {
		btv->sw_status[ix] = ix;
		gv800s_write(btv, ix, ix, 1);
	}

	/* Inputs on the "master" controller need this brightness fix */
	bttv_I2CWrite(btv, 0x18, 0x5, 0x90, 1);

	if (btv->c.nr > BTTV_MAX-4)
		return;
	/*
	 * Store the "master" controller pointer in the master
	 * array for later use in the muxsel function.
	 */
	master[btv->c.nr]   = btv;
	master[btv->c.nr+1] = btv;
	master[btv->c.nr+2] = btv;
	master[btv->c.nr+3] = btv;
}