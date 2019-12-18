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
typedef  int u8 ;
struct TYPE_3__ {scalar_t__ height; scalar_t__ top; } ;
struct TYPE_4__ {TYPE_1__ bounds; } ;
struct bttv_tvnorm {TYPE_2__ cropcap; } ;
struct bttv {size_t tvnorm; scalar_t__ crop_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT848_E_CROP ; 
 int /*<<< orphan*/  BT848_E_VDELAY_LO ; 
 int /*<<< orphan*/  BT848_O_CROP ; 
 int /*<<< orphan*/  BT848_O_VDELAY_LO ; 
 int btread (int /*<<< orphan*/ ) ; 
 struct bttv_tvnorm* bttv_tvnorms ; 
 int /*<<< orphan*/  btwrite (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
disclaim_video_lines(struct bttv *btv)
{
	const struct bttv_tvnorm *tvnorm;
	u8 crop;

	tvnorm = &bttv_tvnorms[btv->tvnorm];
	btv->crop_start = tvnorm->cropcap.bounds.top
		+ tvnorm->cropcap.bounds.height;

	/* VBI capturing ends at VDELAY, start of video capturing, no
	   matter how many lines the VBI RISC program expects. When video
	   capturing is off, it shall no longer "preempt" VBI capturing,
	   so we set VDELAY to maximum. */
	crop = btread(BT848_E_CROP) | 0xc0;
	btwrite(crop, BT848_E_CROP);
	btwrite(0xfe, BT848_E_VDELAY_LO);
	btwrite(crop, BT848_O_CROP);
	btwrite(0xfe, BT848_O_VDELAY_LO);
}