#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {scalar_t__ g450dac; } ;
struct matrox_fb_info {TYPE_3__ altout; TYPE_2__* outputs; TYPE_1__ devflags; } ;
struct TYPE_5__ {void* mode; int /*<<< orphan*/ * data; int /*<<< orphan*/ * output; void* src; } ;

/* Variables and functions */
 void* MATROXFB_OUTPUT_MODE_MONITOR ; 
 void* MATROXFB_SRC_NONE ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

void matroxfb_g450_shutdown(struct matrox_fb_info *minfo)
{
	if (minfo->devflags.g450dac) {
		down_write(&minfo->altout.lock);
		minfo->outputs[1].src = MATROXFB_SRC_NONE;
		minfo->outputs[1].output = NULL;
		minfo->outputs[1].data = NULL;
		minfo->outputs[1].mode = MATROXFB_OUTPUT_MODE_MONITOR;
		minfo->outputs[2].src = MATROXFB_SRC_NONE;
		minfo->outputs[2].output = NULL;
		minfo->outputs[2].data = NULL;
		minfo->outputs[2].mode = MATROXFB_OUTPUT_MODE_MONITOR;
		up_write(&minfo->altout.lock);
	}
}