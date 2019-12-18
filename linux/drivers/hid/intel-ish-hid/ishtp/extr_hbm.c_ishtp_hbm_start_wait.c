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
struct ishtp_device {int /*<<< orphan*/  hbm_state; int /*<<< orphan*/  devc; int /*<<< orphan*/  wait_hbm_recvd_msg; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int HZ ; 
 int /*<<< orphan*/  ISHTP_HBM_IDLE ; 
 int /*<<< orphan*/  ISHTP_HBM_START ; 
 int /*<<< orphan*/  ISHTP_HBM_STARTED ; 
 int ISHTP_INTEROP_TIMEOUT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int) ; 

int ishtp_hbm_start_wait(struct ishtp_device *dev)
{
	int ret;

	if (dev->hbm_state > ISHTP_HBM_START)
		return 0;

	dev_dbg(dev->devc, "Going to wait for ishtp start. hbm_state=%08X\n",
		dev->hbm_state);
	ret = wait_event_interruptible_timeout(dev->wait_hbm_recvd_msg,
					dev->hbm_state >= ISHTP_HBM_STARTED,
					(ISHTP_INTEROP_TIMEOUT * HZ));

	dev_dbg(dev->devc,
		"Woke up from waiting for ishtp start. hbm_state=%08X\n",
		dev->hbm_state);

	if (ret <= 0 && (dev->hbm_state <= ISHTP_HBM_START)) {
		dev->hbm_state = ISHTP_HBM_IDLE;
		dev_err(dev->devc,
		"waiting for ishtp start failed. ret=%d hbm_state=%08X\n",
			ret, dev->hbm_state);
		return -ETIMEDOUT;
	}
	return 0;
}