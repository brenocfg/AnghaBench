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
struct hisi_hba {struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CQE_SEND_CNT ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,...) ; 
 int hisi_sas_read32 (struct hisi_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static void wait_cmds_complete_timeout_v3_hw(struct hisi_hba *hisi_hba,
					     int delay_ms, int timeout_ms)
{
	struct device *dev = hisi_hba->dev;
	int entries, entries_old = 0, time;

	for (time = 0; time < timeout_ms; time += delay_ms) {
		entries = hisi_sas_read32(hisi_hba, CQE_SEND_CNT);
		if (entries == entries_old)
			break;

		entries_old = entries;
		msleep(delay_ms);
	}

	if (time >= timeout_ms) {
		dev_dbg(dev, "Wait commands complete timeout!\n");
		return;
	}

	dev_dbg(dev, "wait commands complete %dms\n", time);
}