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
struct urb {int status; int /*<<< orphan*/  transfer_buffer; struct mdc800_data* context; } ;
struct mdc800_data {int out_count; scalar_t__ download_left; int downloaded; int /*<<< orphan*/  download_wait; TYPE_1__* dev; int /*<<< orphan*/  state; scalar_t__ out_ptr; int /*<<< orphan*/  out; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  READY ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mdc800_usb_download_notify (struct urb *urb)
{
	struct mdc800_data* mdc800=urb->context;
	int status = urb->status;

	if (status == 0) {
		/* Fill output buffer with these data */
		memcpy (mdc800->out,  urb->transfer_buffer, 64);
		mdc800->out_count=64;
		mdc800->out_ptr=0;
		mdc800->download_left-=64;
		if (mdc800->download_left == 0)
		{
			mdc800->state=READY;
		}
	} else {
		dev_err(&mdc800->dev->dev,
			"request bytes fails (status:%i)\n", status);
	}
	mdc800->downloaded = 1;
	wake_up (&mdc800->download_wait);
}