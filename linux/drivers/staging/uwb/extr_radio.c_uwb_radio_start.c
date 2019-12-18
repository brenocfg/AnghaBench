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
struct TYPE_2__ {int /*<<< orphan*/  mutex; } ;
struct uwb_rc {TYPE_1__ uwb_dev; int /*<<< orphan*/  active_pals; } ;
struct uwb_pal {int channel; struct uwb_rc* rc; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int uwb_radio_change_channel (struct uwb_rc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uwb_radio_select_channel (struct uwb_rc*) ; 

int uwb_radio_start(struct uwb_pal *pal)
{
	struct uwb_rc *rc = pal->rc;
	int ret = 0;

	mutex_lock(&rc->uwb_dev.mutex);

	if (!pal->channel) {
		pal->channel = -1;
		rc->active_pals++;
		ret = uwb_radio_change_channel(rc, uwb_radio_select_channel(rc));
	}

	mutex_unlock(&rc->uwb_dev.mutex);
	return ret;
}