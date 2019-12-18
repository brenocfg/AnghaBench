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
struct hv_uio_private_data {int /*<<< orphan*/  recv_buf; scalar_t__ recv_gpadl; int /*<<< orphan*/  send_buf; scalar_t__ send_gpadl; } ;
struct hv_device {int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmbus_teardown_gpadl (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
hv_uio_cleanup(struct hv_device *dev, struct hv_uio_private_data *pdata)
{
	if (pdata->send_gpadl) {
		vmbus_teardown_gpadl(dev->channel, pdata->send_gpadl);
		pdata->send_gpadl = 0;
		vfree(pdata->send_buf);
	}

	if (pdata->recv_gpadl) {
		vmbus_teardown_gpadl(dev->channel, pdata->recv_gpadl);
		pdata->recv_gpadl = 0;
		vfree(pdata->recv_buf);
	}
}