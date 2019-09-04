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
struct urb {int /*<<< orphan*/  dev; scalar_t__ context; } ;
struct TYPE_3__ {scalar_t__ ctrl_out_idx; scalar_t__ ctrl_cnt; int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__ hfcusb_data ;

/* Variables and functions */
 scalar_t__ HFC_CTRL_BUFSIZE ; 
 int /*<<< orphan*/  ctrl_start_transfer (TYPE_1__*) ; 

__attribute__((used)) static void
ctrl_complete(struct urb *urb)
{
	hfcusb_data *hfc = (hfcusb_data *) urb->context;

	urb->dev = hfc->dev;
	if (hfc->ctrl_cnt) {
		hfc->ctrl_cnt--;	/* decrement actual count */
		if (++hfc->ctrl_out_idx >= HFC_CTRL_BUFSIZE)
			hfc->ctrl_out_idx = 0;	/* pointer wrap */

		ctrl_start_transfer(hfc);	/* start next transfer */
	}
}