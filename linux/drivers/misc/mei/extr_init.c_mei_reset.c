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
struct mei_device {int dev_state; scalar_t__ reset_count; int /*<<< orphan*/  dev; int /*<<< orphan*/  rd_msg_hdr; } ;
typedef  enum mei_dev_state { ____Placeholder_mei_dev_state } mei_dev_state ;

/* Variables and functions */
 int ENODEV ; 
 int MEI_DEV_DISABLED ; 
 int MEI_DEV_INITIALIZING ; 
 int MEI_DEV_INIT_CLIENTS ; 
 int MEI_DEV_POWER_DOWN ; 
 int MEI_DEV_POWER_UP ; 
 int MEI_DEV_RESETTING ; 
 int MEI_FW_STATUS_STR_SZ ; 
 scalar_t__ MEI_MAX_CONSEC_RESET ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mei_cl_all_disconnect (struct mei_device*) ; 
 int /*<<< orphan*/  mei_clear_interrupts (struct mei_device*) ; 
 int /*<<< orphan*/  mei_dev_state_str (int) ; 
 int /*<<< orphan*/  mei_fw_status_str (struct mei_device*,char*,int) ; 
 int /*<<< orphan*/  mei_hbm_idle (struct mei_device*) ; 
 int /*<<< orphan*/  mei_hbm_reset (struct mei_device*) ; 
 int mei_hbm_start_req (struct mei_device*) ; 
 int mei_hw_reset (struct mei_device*,int) ; 
 int mei_hw_start (struct mei_device*) ; 
 int /*<<< orphan*/  mei_set_devstate (struct mei_device*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int mei_reset(struct mei_device *dev)
{
	enum mei_dev_state state = dev->dev_state;
	bool interrupts_enabled;
	int ret;

	if (state != MEI_DEV_INITIALIZING &&
	    state != MEI_DEV_DISABLED &&
	    state != MEI_DEV_POWER_DOWN &&
	    state != MEI_DEV_POWER_UP) {
		char fw_sts_str[MEI_FW_STATUS_STR_SZ];

		mei_fw_status_str(dev, fw_sts_str, MEI_FW_STATUS_STR_SZ);
		dev_warn(dev->dev, "unexpected reset: dev_state = %s fw status = %s\n",
			 mei_dev_state_str(state), fw_sts_str);
	}

	mei_clear_interrupts(dev);

	/* we're already in reset, cancel the init timer
	 * if the reset was called due the hbm protocol error
	 * we need to call it before hw start
	 * so the hbm watchdog won't kick in
	 */
	mei_hbm_idle(dev);

	/* enter reset flow */
	interrupts_enabled = state != MEI_DEV_POWER_DOWN;
	mei_set_devstate(dev, MEI_DEV_RESETTING);

	dev->reset_count++;
	if (dev->reset_count > MEI_MAX_CONSEC_RESET) {
		dev_err(dev->dev, "reset: reached maximal consecutive resets: disabling the device\n");
		mei_set_devstate(dev, MEI_DEV_DISABLED);
		return -ENODEV;
	}

	ret = mei_hw_reset(dev, interrupts_enabled);
	/* fall through and remove the sw state even if hw reset has failed */

	/* no need to clean up software state in case of power up */
	if (state != MEI_DEV_INITIALIZING && state != MEI_DEV_POWER_UP)
		mei_cl_all_disconnect(dev);

	mei_hbm_reset(dev);

	memset(dev->rd_msg_hdr, 0, sizeof(dev->rd_msg_hdr));

	if (ret) {
		dev_err(dev->dev, "hw_reset failed ret = %d\n", ret);
		return ret;
	}

	if (state == MEI_DEV_POWER_DOWN) {
		dev_dbg(dev->dev, "powering down: end of reset\n");
		mei_set_devstate(dev, MEI_DEV_DISABLED);
		return 0;
	}

	ret = mei_hw_start(dev);
	if (ret) {
		dev_err(dev->dev, "hw_start failed ret = %d\n", ret);
		return ret;
	}

	dev_dbg(dev->dev, "link is established start sending messages.\n");

	mei_set_devstate(dev, MEI_DEV_INIT_CLIENTS);
	ret = mei_hbm_start_req(dev);
	if (ret) {
		dev_err(dev->dev, "hbm_start failed ret = %d\n", ret);
		mei_set_devstate(dev, MEI_DEV_RESETTING);
		return ret;
	}

	return 0;
}