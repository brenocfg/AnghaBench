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
struct ishtp_device {int /*<<< orphan*/  devc; int /*<<< orphan*/  recvd_hw_ready; int /*<<< orphan*/  wait_hw_ready; } ;

/* Variables and functions */
 int ENODEV ; 
 int HZ ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ish_set_host_rdy (struct ishtp_device*) ; 
 int /*<<< orphan*/  ish_wakeup (struct ishtp_device*) ; 
 int /*<<< orphan*/  set_host_ready (struct ishtp_device*) ; 
 int /*<<< orphan*/  wait_event_interruptible_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int ish_hw_start(struct ishtp_device *dev)
{
	ish_set_host_rdy(dev);

	set_host_ready(dev);

	/* After that we can enable ISH DMA operation and wakeup ISHFW */
	ish_wakeup(dev);

	/* wait for FW-initiated reset flow */
	if (!dev->recvd_hw_ready)
		wait_event_interruptible_timeout(dev->wait_hw_ready,
						 dev->recvd_hw_ready,
						 10 * HZ);

	if (!dev->recvd_hw_ready) {
		dev_err(dev->devc,
			"[ishtp-ish]: Timed out waiting for FW-initiated reset\n");
		return	-ENODEV;
	}

	return 0;
}