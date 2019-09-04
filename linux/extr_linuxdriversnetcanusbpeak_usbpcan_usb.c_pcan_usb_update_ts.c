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
struct pcan_usb_msg_context {scalar_t__ end; scalar_t__ rec_idx; int /*<<< orphan*/  ts16; TYPE_1__* pdev; int /*<<< orphan*/  ptr; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_2__ {int /*<<< orphan*/  time_ref; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  peak_usb_set_ts_now (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  peak_usb_update_ts_now (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pcan_usb_update_ts(struct pcan_usb_msg_context *mc)
{
	__le16 tmp16;

	if ((mc->ptr+2) > mc->end)
		return -EINVAL;

	memcpy(&tmp16, mc->ptr, 2);

	mc->ts16 = le16_to_cpu(tmp16);

	if (mc->rec_idx > 0)
		peak_usb_update_ts_now(&mc->pdev->time_ref, mc->ts16);
	else
		peak_usb_set_ts_now(&mc->pdev->time_ref, mc->ts16);

	return 0;
}