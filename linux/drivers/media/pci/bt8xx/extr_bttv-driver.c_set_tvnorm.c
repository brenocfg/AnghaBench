#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  v4l2_std_id ;
struct TYPE_5__ {scalar_t__ height; scalar_t__ top; } ;
struct TYPE_7__ {TYPE_1__ bounds; } ;
struct bttv_tvnorm {int adelay; int bdelay; int vbipack; int /*<<< orphan*/  v4l2_id; int /*<<< orphan*/  iform; TYPE_3__ cropcap; } ;
struct TYPE_6__ {int type; } ;
struct bttv {unsigned int tvnorm; int resources; TYPE_2__ c; scalar_t__ crop_start; int /*<<< orphan*/ * crop; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT848_ADELAY ; 
 int /*<<< orphan*/  BT848_BDELAY ; 
 int /*<<< orphan*/  BT848_IFORM ; 
 int BT848_IFORM_NORM ; 
 int BT848_IFORM_XTBOTH ; 
 int /*<<< orphan*/  BT848_VBI_PACK_DEL ; 
 int /*<<< orphan*/  BT848_VBI_PACK_SIZE ; 
#define  BTTV_BOARD_VOODOOTV_200 129 
#define  BTTV_BOARD_VOODOOTV_FM 128 
 unsigned int BTTV_TVNORMS ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int VIDEO_RESOURCES ; 
 int /*<<< orphan*/  bt848A_set_timing (struct bttv*) ; 
 int /*<<< orphan*/  btaor (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bttv_call_all (struct bttv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bttv_crop_reset (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  bttv_tda9880_setnorm (struct bttv*,int /*<<< orphan*/ ) ; 
 struct bttv_tvnorm* bttv_tvnorms ; 
 int /*<<< orphan*/  btwrite (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_read () ; 
 scalar_t__ memcmp (TYPE_3__*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  s_std ; 
 int /*<<< orphan*/  video ; 

__attribute__((used)) static int
set_tvnorm(struct bttv *btv, unsigned int norm)
{
	const struct bttv_tvnorm *tvnorm;
	v4l2_std_id id;

	BUG_ON(norm >= BTTV_TVNORMS);
	BUG_ON(btv->tvnorm >= BTTV_TVNORMS);

	tvnorm = &bttv_tvnorms[norm];

	if (memcmp(&bttv_tvnorms[btv->tvnorm].cropcap, &tvnorm->cropcap,
		    sizeof (tvnorm->cropcap))) {
		bttv_crop_reset(&btv->crop[0], norm);
		btv->crop[1] = btv->crop[0]; /* current = default */

		if (0 == (btv->resources & VIDEO_RESOURCES)) {
			btv->crop_start = tvnorm->cropcap.bounds.top
				+ tvnorm->cropcap.bounds.height;
		}
	}

	btv->tvnorm = norm;

	btwrite(tvnorm->adelay, BT848_ADELAY);
	btwrite(tvnorm->bdelay, BT848_BDELAY);
	btaor(tvnorm->iform,~(BT848_IFORM_NORM|BT848_IFORM_XTBOTH),
	      BT848_IFORM);
	btwrite(tvnorm->vbipack, BT848_VBI_PACK_SIZE);
	btwrite(1, BT848_VBI_PACK_DEL);
	bt848A_set_timing(btv);

	switch (btv->c.type) {
	case BTTV_BOARD_VOODOOTV_FM:
	case BTTV_BOARD_VOODOOTV_200:
		bttv_tda9880_setnorm(btv, gpio_read());
		break;
	}
	id = tvnorm->v4l2_id;
	bttv_call_all(btv, video, s_std, id);

	return 0;
}