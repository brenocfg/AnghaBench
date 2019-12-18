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
struct hidled_device {int /*<<< orphan*/  lock; TYPE_1__* config; int /*<<< orphan*/ * buf; int /*<<< orphan*/  hdev; } ;
typedef  int /*<<< orphan*/  __u8 ;
struct TYPE_2__ {scalar_t__ report_type; int /*<<< orphan*/  report_size; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HID_FEATURE_REPORT ; 
 int /*<<< orphan*/  HID_REQ_GET_REPORT ; 
 int /*<<< orphan*/  HID_REQ_SET_REPORT ; 
 scalar_t__ RAW_REQUEST ; 
 int hid_hw_raw_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hidled_recv(struct hidled_device *ldev, __u8 *buf)
{
	int ret;

	if (ldev->config->report_type != RAW_REQUEST)
		return -EINVAL;

	mutex_lock(&ldev->lock);

	memcpy(ldev->buf, buf, ldev->config->report_size);

	ret = hid_hw_raw_request(ldev->hdev, buf[0], ldev->buf,
				 ldev->config->report_size,
				 HID_FEATURE_REPORT,
				 HID_REQ_SET_REPORT);
	if (ret < 0)
		goto err;

	ret = hid_hw_raw_request(ldev->hdev, buf[0], ldev->buf,
				 ldev->config->report_size,
				 HID_FEATURE_REPORT,
				 HID_REQ_GET_REPORT);

	memcpy(buf, ldev->buf, ldev->config->report_size);
err:
	mutex_unlock(&ldev->lock);

	return ret < 0 ? ret : 0;
}