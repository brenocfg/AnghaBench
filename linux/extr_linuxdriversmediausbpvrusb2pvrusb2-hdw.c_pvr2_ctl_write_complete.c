#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct urb {struct pvr2_hdw* context; } ;
struct pvr2_hdw {int /*<<< orphan*/  ctl_done; scalar_t__ ctl_read_pend_flag; scalar_t__ ctl_write_pend_flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pvr2_ctl_write_complete(struct urb *urb)
{
	struct pvr2_hdw *hdw = urb->context;
	hdw->ctl_write_pend_flag = 0;
	if (hdw->ctl_read_pend_flag) return;
	complete(&hdw->ctl_done);
}