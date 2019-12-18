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
typedef  int /*<<< orphan*/  u8 ;
struct dj_device {int /*<<< orphan*/  hdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HID_INPUT_REPORT ; 
 int /*<<< orphan*/  dbg_hid (char*) ; 
 scalar_t__ hid_input_report (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void logi_dj_recv_forward_report(struct dj_device *dj_dev, u8 *data,
					int size)
{
	/* We are called from atomic context (tasklet && djrcv->lock held) */
	if (hid_input_report(dj_dev->hdev, HID_INPUT_REPORT, data, size, 1))
		dbg_hid("hid_input_report error\n");
}