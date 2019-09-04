#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wm97xx {scalar_t__ id; int /*<<< orphan*/  dev; int /*<<< orphan*/  acc_slot; int /*<<< orphan*/  acc_rate; int /*<<< orphan*/ * ac97; } ;
struct TYPE_3__ {scalar_t__ id; scalar_t__ speed; int /*<<< orphan*/  code; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int ENODEV ; 
 int /*<<< orphan*/  ac97_touch_slot ; 
 TYPE_1__* cinfo ; 
 scalar_t__ cont_rate ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 size_t sp_idx ; 

__attribute__((used)) static int wm97xx_acc_startup(struct wm97xx *wm)
{
	int idx;

	/* check we have a codec */
	if (wm->ac97 == NULL)
		return -ENODEV;

	/* Go you big red fire engine */
	for (idx = 0; idx < ARRAY_SIZE(cinfo); idx++) {
		if (wm->id != cinfo[idx].id)
			continue;
		sp_idx = idx;
		if (cont_rate <= cinfo[idx].speed)
			break;
	}
	wm->acc_rate = cinfo[sp_idx].code;
	wm->acc_slot = ac97_touch_slot;
	dev_info(wm->dev,
		 "zylonite accelerated touchscreen driver, %d samples/sec\n",
		 cinfo[sp_idx].speed);

	return 0;
}