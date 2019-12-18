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
struct u2fzero_device {int /*<<< orphan*/  lock; int /*<<< orphan*/  buf_out; int /*<<< orphan*/  hdev; } ;
struct u2f_hid_report {int dummy; } ;
struct u2f_hid_msg {int dummy; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int hid_hw_output_report (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,struct u2f_hid_report*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int u2fzero_send(struct u2fzero_device *dev, struct u2f_hid_report *req)
{
	int ret;

	mutex_lock(&dev->lock);

	memcpy(dev->buf_out, req, sizeof(struct u2f_hid_report));

	ret = hid_hw_output_report(dev->hdev, dev->buf_out,
				   sizeof(struct u2f_hid_msg));

	mutex_unlock(&dev->lock);

	if (ret < 0)
		return ret;

	return ret == sizeof(struct u2f_hid_msg) ? 0 : -EMSGSIZE;
}