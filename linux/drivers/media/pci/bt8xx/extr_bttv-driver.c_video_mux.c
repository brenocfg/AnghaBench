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
struct TYPE_3__ {size_t type; int /*<<< orphan*/  nr; } ;
struct bttv {unsigned int svhs; TYPE_1__ c; } ;
struct TYPE_4__ {unsigned int video_inputs; int gpiomask2; int /*<<< orphan*/  (* muxsel_hook ) (struct bttv*,unsigned int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BT848_CONTROL_COMP ; 
 int /*<<< orphan*/  BT848_E_CONTROL ; 
 int /*<<< orphan*/  BT848_IFORM ; 
 int /*<<< orphan*/  BT848_O_CONTROL ; 
 int EINVAL ; 
 int /*<<< orphan*/  btand (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btaor (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bttv_muxsel (struct bttv*,unsigned int) ; 
 TYPE_2__* bttv_tvcards ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,unsigned int,int) ; 
 int /*<<< orphan*/  gpio_inout (int,int) ; 
 int /*<<< orphan*/  stub1 (struct bttv*,unsigned int) ; 

__attribute__((used)) static int
video_mux(struct bttv *btv, unsigned int input)
{
	int mux,mask2;

	if (input >= bttv_tvcards[btv->c.type].video_inputs)
		return -EINVAL;

	/* needed by RemoteVideo MX */
	mask2 = bttv_tvcards[btv->c.type].gpiomask2;
	if (mask2)
		gpio_inout(mask2,mask2);

	if (input == btv->svhs)  {
		btor(BT848_CONTROL_COMP, BT848_E_CONTROL);
		btor(BT848_CONTROL_COMP, BT848_O_CONTROL);
	} else {
		btand(~BT848_CONTROL_COMP, BT848_E_CONTROL);
		btand(~BT848_CONTROL_COMP, BT848_O_CONTROL);
	}
	mux = bttv_muxsel(btv, input);
	btaor(mux<<5, ~(3<<5), BT848_IFORM);
	dprintk("%d: video mux: input=%d mux=%d\n", btv->c.nr, input, mux);

	/* card specific hook */
	if(bttv_tvcards[btv->c.type].muxsel_hook)
		bttv_tvcards[btv->c.type].muxsel_hook (btv, input);
	return 0;
}