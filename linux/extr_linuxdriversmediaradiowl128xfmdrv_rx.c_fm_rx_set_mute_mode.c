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
typedef  scalar_t__ u8 ;
struct TYPE_2__ {scalar_t__ mute_mode; } ;
struct fmdev {TYPE_1__ rx; } ;

/* Variables and functions */
 int fm_config_rx_mute_reg (struct fmdev*) ; 

int fm_rx_set_mute_mode(struct fmdev *fmdev, u8 mute_mode_toset)
{
	u8 org_state;
	int ret;

	if (fmdev->rx.mute_mode == mute_mode_toset)
		return 0;

	org_state = fmdev->rx.mute_mode;
	fmdev->rx.mute_mode = mute_mode_toset;

	ret = fm_config_rx_mute_reg(fmdev);
	if (ret < 0) {
		fmdev->rx.mute_mode = org_state;
		return ret;
	}

	return 0;
}