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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  af_mode; } ;
struct fmdev {scalar_t__ curr_fmmode; TYPE_1__ rx; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EPERM ; 
 scalar_t__ FM_MODE_RX ; 
 int /*<<< orphan*/  fmerr (char*) ; 

int fm_rx_get_af_switch(struct fmdev *fmdev, u8 *af_mode)
{
	if (fmdev->curr_fmmode != FM_MODE_RX)
		return -EPERM;

	if (af_mode == NULL) {
		fmerr("Invalid memory\n");
		return -ENOMEM;
	}

	*af_mode = fmdev->rx.af_mode;

	return 0;
}