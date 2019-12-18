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
struct hidled_device {TYPE_1__* config; int /*<<< orphan*/  lock; int /*<<< orphan*/  buf; int /*<<< orphan*/  hdev; } ;
typedef  int /*<<< orphan*/  __u8 ;
struct TYPE_2__ {int report_size; scalar_t__ report_type; } ;

/* Variables and functions */
 int EINVAL ; 
 int EMSGSIZE ; 
 int /*<<< orphan*/  HID_FEATURE_REPORT ; 
 int /*<<< orphan*/  HID_REQ_SET_REPORT ; 
 scalar_t__ OUTPUT_REPORT ; 
 scalar_t__ RAW_REQUEST ; 
 int hid_hw_output_report (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int hid_hw_raw_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hidled_send(struct hidled_device *ldev, __u8 *buf)
{
	int ret;

	mutex_lock(&ldev->lock);

	/*
	 * buffer provided to hid_hw_raw_request must not be on the stack
	 * and must not be part of a data structure
	 */
	memcpy(ldev->buf, buf, ldev->config->report_size);

	if (ldev->config->report_type == RAW_REQUEST)
		ret = hid_hw_raw_request(ldev->hdev, buf[0], ldev->buf,
					 ldev->config->report_size,
					 HID_FEATURE_REPORT,
					 HID_REQ_SET_REPORT);
	else if (ldev->config->report_type == OUTPUT_REPORT)
		ret = hid_hw_output_report(ldev->hdev, ldev->buf,
					   ldev->config->report_size);
	else
		ret = -EINVAL;

	mutex_unlock(&ldev->lock);

	if (ret < 0)
		return ret;

	return ret == ldev->config->report_size ? 0 : -EMSGSIZE;
}