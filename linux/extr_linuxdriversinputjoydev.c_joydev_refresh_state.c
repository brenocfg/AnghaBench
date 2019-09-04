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
struct TYPE_2__ {struct input_dev* dev; } ;
struct joydev {int nabs; int /*<<< orphan*/ * corr; int /*<<< orphan*/ * abs; int /*<<< orphan*/ * abspam; TYPE_1__ handle; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int input_abs_get_val (struct input_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  joydev_correct (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void joydev_refresh_state(struct joydev *joydev)
{
	struct input_dev *dev = joydev->handle.dev;
	int i, val;

	for (i = 0; i < joydev->nabs; i++) {
		val = input_abs_get_val(dev, joydev->abspam[i]);
		joydev->abs[i] = joydev_correct(val, &joydev->corr[i]);
	}
}