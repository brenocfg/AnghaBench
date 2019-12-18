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
struct wkup_m3_ipc {int state; int /*<<< orphan*/  sync_complete; struct device* dev; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int M3_BASELINE_VERSION ; 
 void* M3_STATE_INITED ; 
#define  M3_STATE_MSG_FOR_LP 131 
#define  M3_STATE_MSG_FOR_RESET 130 
#define  M3_STATE_RESET 129 
#define  M3_STATE_UNKNOWN 128 
 int M3_VERSION_UNKNOWN ; 
 int /*<<< orphan*/  am33xx_txev_enable (struct wkup_m3_ipc*) ; 
 int /*<<< orphan*/  am33xx_txev_eoi (struct wkup_m3_ipc*) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,...) ; 
 int wkup_m3_fw_version_read (struct wkup_m3_ipc*) ; 

__attribute__((used)) static irqreturn_t wkup_m3_txev_handler(int irq, void *ipc_data)
{
	struct wkup_m3_ipc *m3_ipc = ipc_data;
	struct device *dev = m3_ipc->dev;
	int ver = 0;

	am33xx_txev_eoi(m3_ipc);

	switch (m3_ipc->state) {
	case M3_STATE_RESET:
		ver = wkup_m3_fw_version_read(m3_ipc);

		if (ver == M3_VERSION_UNKNOWN ||
		    ver < M3_BASELINE_VERSION) {
			dev_warn(dev, "CM3 Firmware Version %x not supported\n",
				 ver);
		} else {
			dev_info(dev, "CM3 Firmware Version = 0x%x\n", ver);
		}

		m3_ipc->state = M3_STATE_INITED;
		complete(&m3_ipc->sync_complete);
		break;
	case M3_STATE_MSG_FOR_RESET:
		m3_ipc->state = M3_STATE_INITED;
		complete(&m3_ipc->sync_complete);
		break;
	case M3_STATE_MSG_FOR_LP:
		complete(&m3_ipc->sync_complete);
		break;
	case M3_STATE_UNKNOWN:
		dev_warn(dev, "Unknown CM3 State\n");
	}

	am33xx_txev_enable(m3_ipc);

	return IRQ_HANDLED;
}