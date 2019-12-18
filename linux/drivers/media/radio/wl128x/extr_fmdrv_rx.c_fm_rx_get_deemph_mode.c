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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int /*<<< orphan*/  deemphasis_mode; } ;
struct fmdev {scalar_t__ curr_fmmode; TYPE_1__ rx; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EPERM ; 
 scalar_t__ FM_MODE_RX ; 
 int /*<<< orphan*/  fmerr (char*) ; 

int fm_rx_get_deemph_mode(struct fmdev *fmdev, u16 *curr_deemphasis_mode)
{
	if (fmdev->curr_fmmode != FM_MODE_RX)
		return -EPERM;

	if (curr_deemphasis_mode == NULL) {
		fmerr("Invalid memory\n");
		return -ENOMEM;
	}

	*curr_deemphasis_mode = fmdev->rx.deemphasis_mode;

	return 0;
}